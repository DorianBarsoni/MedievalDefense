#include "CameraPlayerPawn.h"
#include "Components/BoxComponent.h"

#include "TroopController.h"
#include "AllyComponent.h"
#include "Engine/World.h"

ACameraPlayerPawn::ACameraPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

    UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;
    BoxComponent->SetGenerateOverlapEvents(true);
    BoxComponent->SetCollisionProfileName(TEXT("Pawn"));

    speed = 100;
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

            SelectedTroops.Empty();
            if (Troop && Troop->TeamComponent->IsA(UAllyComponent::StaticClass())) {
                SelectedTroops.Add(Troop);
            }
            //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("TArray num : %d"), SelectedTroops.Num()));
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

