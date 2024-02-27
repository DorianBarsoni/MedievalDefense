#include "CameraPlayerPawn.h"
#include "Components/BoxComponent.h"

#include "TroopController.h"
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

    if (TraceLineFromCameraToMousePosition(HitResult, true)) {

        AActor* HitActor = HitResult.GetActor();
        if (HitActor) {
            FVector HitLocation = HitResult.ImpactPoint;
            ATroopCharacter *Troop = Cast<ATroopCharacter>(HitActor);

            FString name = HitActor->GetActorNameOrLabel();
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, name);

            UnselectTroops();
            if (Troop && Troop->TroopDataAsset->TeamTag.GetTagName() == "Ally") {
                Troop->GetMesh()->SetRenderCustomDepth(true);
                SelectedTroops.Add(Troop);
            }
        }
    }
}

void ACameraPlayerPawn::RightClickPressed() {
    if (!SelectedTroops.IsEmpty()) {
        FHitResult HitResult;
    
        if (TraceLineFromCameraToMousePosition(HitResult, true)) {
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
    if (TraceLineFromCameraToMousePosition(HitResult, false)) {
        if (isFirstHold) {
            HoldAndReleaseCoordinates.Get<0>() = HitResult.ImpactPoint;
            HoldAndReleaseCoordinates.Get<1>() = HitResult.ImpactPoint;
            isFirstHold = false;
        }
        else {
            HoldAndReleaseCoordinates.Get<1>() = HitResult.ImpactPoint;
        }

        float x_len = 0.5 * FMath::Abs(HoldAndReleaseCoordinates.Get<1>().X - HoldAndReleaseCoordinates.Get<0>().X);
        float y_len = 0.5 * FMath::Abs(HoldAndReleaseCoordinates.Get<1>().Y - HoldAndReleaseCoordinates.Get<0>().Y);
        float z_len = 0.5 * FMath::Abs(HoldAndReleaseCoordinates.Get<1>().Z - HoldAndReleaseCoordinates.Get<0>().Z);
        FVector HalfSize = FVector(x_len, y_len, 1);

        DrawDebugBox(GetWorld(), getMiddlePoint(), HalfSize, FQuat::Identity, FColor::Green, false, 0.05, 0, 5.0);
    }
}

void ACameraPlayerPawn::LeftClickHoldAndReleased() {
    FHitResult HitResult;
    if (TraceLineFromCameraToMousePosition(HitResult, false)) {
        HoldAndReleaseCoordinates.Get<1>() = HitResult.ImpactPoint;
        isFirstHold = true;

        float x_len = 0.5 * FMath::Abs(HoldAndReleaseCoordinates.Get<1>().X - HoldAndReleaseCoordinates.Get<0>().X);
        float y_len = 0.5 * FMath::Abs(HoldAndReleaseCoordinates.Get<1>().Y - HoldAndReleaseCoordinates.Get<0>().Y);
        FVector HalfSize = FVector(x_len, y_len, 10000);

        TArray<FHitResult> HitResults;

        FCollisionShape Shape = FCollisionShape::MakeBox(HalfSize);
        TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
        ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

        TArray<AActor*> ActorsToIgnore;
        ActorsToIgnore.Add(this);

        TArray<AActor*> OutActors;

        UnselectTroops();
        if (UKismetSystemLibrary::BoxOverlapActors(this, getMiddlePoint(), HalfSize, ObjectTypes, ATroopCharacter::StaticClass(), ActorsToIgnore, OutActors)) {
            for (auto Actor : OutActors) {
                if (IsValid(Actor) && Actor->GetClass()->IsChildOf(ATroopCharacter::StaticClass())) {
                    ATroopCharacter* TroopCharacter = Cast<ATroopCharacter>(Actor);
                    if (TroopCharacter && TroopCharacter->TroopDataAsset->TeamTag.GetTagName() == "Ally") {
                        SelectedTroops.Add(TroopCharacter);
                        TroopCharacter->GetMesh()->SetRenderCustomDepth(true);
                    }
                }
            }
        }

        //DrawDebugBox(GetWorld(), middlePoint, HalfSize, FQuat::Identity, FColor::Orange, false, 10.0f);
    }
}

bool ACameraPlayerPawn::TraceLineFromCameraToMousePosition(FHitResult &HitResult, bool showHit) {
    APlayerController* PlayerController = Cast<APlayerController>(GetController());

    FVector MouseWorldPosition, MouseWorldDirection;
    PlayerController->DeprojectMousePositionToWorld(MouseWorldPosition, MouseWorldDirection);
    FVector Direction = MouseWorldPosition + 10000.0 * MouseWorldDirection;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    CollisionParams.AddIgnoredActor(GetController());

    if (GetWorld()->LineTraceSingleByChannel(HitResult, MouseWorldPosition, Direction, ECC_Pawn, CollisionParams)) {
        if (showHit) {
            DrawDebugLine(GetWorld(), MouseWorldPosition, Direction, FColor::Red, false, 5.0f, 0, 0.1f);
        }
        return true;
    }
    return false;
}

void ACameraPlayerPawn::SelectTroops(TArray<ATroopCharacter*> NewSelectedTroops) {
    SelectedTroops = NewSelectedTroops;

    for (auto Troop : SelectedTroops) {
        Troop->GetMesh()->SetRenderCustomDepth(true);
    }
}

void ACameraPlayerPawn::UnselectTroops() {
    for (auto Troop : SelectedTroops) {
        Troop->GetMesh()->SetRenderCustomDepth(false);
    }

    SelectedTroops.Empty();
}

FVector ACameraPlayerPawn::getMiddlePoint() {
    return 0.5 * (HoldAndReleaseCoordinates.Get<1>() - HoldAndReleaseCoordinates.Get<0>()) + HoldAndReleaseCoordinates.Get<0>();
}

