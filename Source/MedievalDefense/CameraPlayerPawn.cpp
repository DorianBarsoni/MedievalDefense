#include "CameraPlayerPawn.h"
#include "Components/BoxComponent.h"

#include "TroopController.h"
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
    APlayerController *PlayerController = Cast<APlayerController>(GetController());

    FVector MouseWorldPosition, MouseWorldDirection;
    PlayerController->DeprojectMousePositionToWorld(MouseWorldPosition, MouseWorldDirection);
    FVector Direction = MouseWorldPosition + 10000.0 * MouseWorldDirection;

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    CollisionParams.AddIgnoredActor(GetController());

    if (GetWorld()->LineTraceSingleByChannel(HitResult, MouseWorldPosition, Direction, ECC_Pawn, CollisionParams)) {

        AActor* HitActor = HitResult.GetActor();
        if (HitActor) {
            FVector HitLocation = HitResult.ImpactPoint;
            ATroopCharacter *Troop = Cast<ATroopCharacter>(HitActor);

            FString name = HitActor->GetActorNameOrLabel();
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, name);

            if (Troop) {
                TArray<ATroopCharacter*> NewSelectedTroops;
                NewSelectedTroops.Add(Troop);
                SelectTroops(NewSelectedTroops);
                
            }
            else {
                SelectedTroops.Empty();
            }

            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("TArray num : %d"), SelectedTroops.Num()));
            
        }
        DrawDebugLine(GetWorld(), MouseWorldPosition, Direction, FColor::Red, false, 5.0f, 0, 0.1f);
    }
}

void ACameraPlayerPawn::RightClickPressed() {
    if (!SelectedTroops.IsEmpty()) {
        APlayerController* PlayerController = Cast<APlayerController>(GetController());

        FVector MouseWorldPosition, MouseWorldDirection;
        PlayerController->DeprojectMousePositionToWorld(MouseWorldPosition, MouseWorldDirection);
        FVector Direction = MouseWorldPosition + 10000.0 * MouseWorldDirection;

        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(this);
        CollisionParams.AddIgnoredActor(GetController());

        if (GetWorld()->LineTraceSingleByChannel(HitResult, MouseWorldPosition, Direction, ECC_Pawn, CollisionParams)) {
            for (auto Troop : SelectedTroops) {
                ATroopController* TroopController = Cast<ATroopController>(Troop->GetController());
                TroopController->MoveTroopToLocation(HitResult.ImpactPoint);
            }
        }
    }
}

void ACameraPlayerPawn::SelectTroops(TArray<ATroopCharacter*> NewSelectedTroops) {
    SelectedTroops = NewSelectedTroops;
}

