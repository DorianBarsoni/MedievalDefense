#include "CameraPlayerPawn.h"
#include "Components/BoxComponent.h"

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

    if (GetWorld()->LineTraceSingleByChannel(HitResult, MouseWorldPosition, Direction, ECC_Visibility, CollisionParams)) {

        AActor* HitActor = HitResult.GetActor();
        if (HitActor) {
            FVector HitLocation = HitResult.ImpactPoint;

            FString Message = FString::Printf(TEXT("Collision à : X=%.2f, Y=%.2f, Z=%.2f"), HitLocation.X, HitLocation.Y, HitLocation.Z);
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Message);

            if (HitActor->IsA(ATroopCharacter::StaticClass())) {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("True"));
            }
            else {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString("False"));
            }

            ATroopCharacter *Troop = Cast<ATroopCharacter>(HitActor);
            Message = FString::Printf(TEXT("TArray size : %d"), SelectedTroops.Num());

            if (Troop) {
                TArray<ATroopCharacter*> NewSelectedTroops;
                NewSelectedTroops.Add(Troop);
                SelectTroops(NewSelectedTroops);

                Message = FString::Printf(TEXT("TArray size : %d, %d"), SelectedTroops.Num(), Troop->LifeComponent->GetLife());
            }
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Message);
        }

        DrawDebugLine(GetWorld(), MouseWorldPosition, Direction, FColor::Red, false, 5.0f, 0, 0.1f);

    }
    
}

void ACameraPlayerPawn::SelectTroops(TArray<ATroopCharacter*> NewSelectedTroops) {
    SelectedTroops = NewSelectedTroops;
}

