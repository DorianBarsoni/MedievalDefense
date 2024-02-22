#include "TroopCharacter.h"
#include "AllyComponent.h"
#include "EnemyComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ATroopCharacter::ATroopCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));
	TeamComponent = CreateDefaultSubobject<UTeamComponent>(TEXT("TeamComponent"));
	TroopDataAsset = CreateDefaultSubobject<UTroopDataAsset>(TEXT("TroopDataAsset"));
}

void ATroopCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (LifeComponent) {
		LifeComponent->SetLife(TroopDataAsset->LifePoint);
	} else UE_LOG(LogTemp, Error, TEXT("LifeComponent is not valid in ATroopCharacter::BeginPlay"));
	
	UCharacterMovementComponent* MyCharacterMovement = GetCharacterMovement();
	if (MyCharacterMovement) {
		MyCharacterMovement->MaxWalkSpeed = TroopDataAsset->SpeedMovement;
	} else UE_LOG(LogTemp, Error, TEXT("CharacterMovement is not valid in ATroopCharacter::BeginPlay"));
	
}

void ATroopCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATroopCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATroopCharacter::MakeTroopAlly() {
	UAllyComponent* AllyComponent = Cast<UAllyComponent>(TeamComponent);

	if (!AllyComponent)
	{
		TeamComponent = NewObject<UAllyComponent>(this, TEXT("AllyComponent"));
		TeamComponent->RegisterComponent();
	}
}

void ATroopCharacter::MakeTroopEnemy() {
	UEnemyComponent* EnemyComponent = Cast<UEnemyComponent>(TeamComponent);

	if (!EnemyComponent)
	{
		TeamComponent = NewObject<UEnemyComponent>(this, TEXT("EnemyComponent"));
		TeamComponent->RegisterComponent();
	}
}

