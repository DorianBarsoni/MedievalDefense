#include "CameraPlayerPawn.h"
#include "Components/BoxComponent.h"

#include "TroopController.h"
#include "AllyComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"

ACameraPlayerPawn::ACameraPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

    UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;
    BoxComponent->SetGenerateOverlapEvents(true);
    BoxComponent->SetCollisionProfileName(TEXT("Pawn"));

    speed = 100;
    isFirstHold = true;
}

void ACameraPlayerPawn::BeginPlay()
{
    Super::BeginPlay();
}

void ACameraPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACameraPlayerPawn::LeftMousePressed() {
    FHitResult HitResult;

    if (TraceLineFromCameraToMousePosition(HitResult)) {

        AActor* HitActor = HitResult.GetActor();
        if (HitActor) {
            FVector HitLocation = HitResult.ImpactPoint;
            ATroopCharacter *Troop = Cast<ATroopCharacter>(HitActor);

            FString name = HitActor->GetActorNameOrLabel();
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, name);

            UnselectTroops();
            if (Troop && Troop->TeamComponent->IsA(UAllyComponent::StaticClass())) {
                Troop->GetMesh()->SetRenderCustomDepth(true);
                SelectedTroops.Add(Troop);
            }
        }
    }
}

void ACameraPlayerPawn::RightClickPressed() {
    if (!SelectedTroops.IsEmpty()) {
        FHitResult HitResult;
    
        if (TraceLineFromCameraToMousePosition(HitResult)) {
            for (auto Troop : SelectedTroops) {
                ATroopController* TroopController = Cast<ATroopController>(Troop->GetController());
                if (TroopController) {
                    TroopController->MoveTroopToLocation(HitResult.ImpactPoint);
                }
            }
        }
    }
}

void ACameraPlayerPawn::LeftClickHold() {

    FHitResult HitResult;
    if (TraceLineFromCameraToMousePosition(HitResult)) {
        if (isFirstHold) {
            HoldAndReleaseCoordinates.Get<0>() = HitResult.ImpactPoint;
            isFirstHold = false;
        }
        else {
            HoldAndReleaseCoordinates.Get<1>() = HitResult.ImpactPoint;
        }
    }
}

FVector ACameraPlayerPawn::LeftClickHoldAndReleased() {
    FHitResult HitResult;
    if (TraceLineFromCameraToMousePosition(HitResult)) {
        HoldAndReleaseCoordinates.Get<1>() = HitResult.ImpactPoint;
        isFirstHold = true;
        
        FVector middlePoint = 0.5*(HoldAndReleaseCoordinates.Get<1>() - HoldAndReleaseCoordinates.Get<0>()) + HoldAndReleaseCoordinates.Get<0>();


        float x_len = 0.5*FMath::Abs(HoldAndReleaseCoordinates.Get<1>().X - HoldAndReleaseCoordinates.Get<0>().X);
        float y_len = 0.5 * FMath::Abs(HoldAndReleaseCoordinates.Get<1>().Y - HoldAndReleaseCoordinates.Get<0>().Y);
        float z_len = 0.5 * FMath::Abs(HoldAndReleaseCoordinates.Get<1>().Z - HoldAndReleaseCoordinates.Get<0>().Z);
        FVector HalfSize = FVector(x_len, y_len, 5000);


        TArray<FHitResult> HitResults;

        UKismetSystemLibrary::BoxTraceMulti(
            this,
            GetActorLocation(),
            middlePoint,
            HalfSize,
            FRotator(0, 0, 0),
            UEngineTypes::ConvertToTraceType(ECC_Pawn),
            false,
            TArray<AActor*>(),
            EDrawDebugTrace::Persistent,
            HitResults,
            true);

        for (const FHitResult& HitResult2 : HitResults) {
            AActor* HitActor = HitResult2.GetActor();

            FString name = HitActor->GetActorNameOrLabel();
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, name);

            if (HitActor && HitActor->IsA(ATroopCharacter::StaticClass())) {
                ATroopCharacter* TroopCharacter = Cast<ATroopCharacter>(HitActor);
                if (TroopCharacter) {
                    SelectedTroops.Add(TroopCharacter);
                }
            }
        }

        DrawDebugBox(GetWorld(), middlePoint, HalfSize, FQuat::Identity, FColor::Orange, false, 10.0f);

        return middlePoint;
        
    }

    return FVector();
}

bool ACameraPlayerPawn::TraceLineFromCameraToMousePosition(FHitResult &HitResult) {
    APlayerController* PlayerController = Cast<APlayerController>(GetController());

    FVector MouseWorldPosition, MouseWorldDirection;
    PlayerController->DeprojectMousePositionToWorld(MouseWorldPosition, MouseWorldDirection);
    FVector Direction = MouseWorldPosition + 10000.0 * MouseWorldDirection;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    CollisionParams.AddIgnoredActor(GetController());

    if (GetWorld()->LineTraceSingleByChannel(HitResult, MouseWorldPosition, Direction, ECC_Pawn, CollisionParams)) {
        DrawDebugLine(GetWorld(), MouseWorldPosition, Direction, FColor::Red, false, 5.0f, 0, 0.1f);
        return true;
    }
    return false;
}

void ACameraPlayerPawn::SelectTroops(TArray<ATroopCharacter*> NewSelectedTroops) {
    SelectedTroops = NewSelectedTroops;
}

void ACameraPlayerPawn::UnselectTroops() {
    for (auto Troop : SelectedTroops) {
        Troop->GetMesh()->SetRenderCustomDepth(false);
    }

    SelectedTroops.Empty();
}

