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
	HealthBarWidgetComponent = CreateDefaultSubobject<UHealthBarWidgetComponent>(TEXT("HealthBarWidgetComponent"));
}

void ATroopCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (LifeComponent) {
		LifeComponent->Life = TroopDataAsset->LifePoint;
		LifeComponent->MaxLife = TroopDataAsset->MaxLifePoint;
	} else UE_LOG(LogTemp, Error, TEXT("LifeComponent is not valid in ATroopCharacter::BeginPlay"));
	
	UCharacterMovementComponent* MyCharacterMovement = GetCharacterMovement();
	if (MyCharacterMovement) {
		MyCharacterMovement->MaxWalkSpeed = TroopDataAsset->SpeedMovement;
	} else UE_LOG(LogTemp, Error, TEXT("CharacterMovement is not valid in ATroopCharacter::BeginPlay"));

	HealthBarWidgetComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	HealthBarWidgetComponent->ChangeHealthPoints(TroopDataAsset->LifePoint, TroopDataAsset->MaxLifePoint);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Troop : %d %d"), TroopDataAsset->LifePoint, TroopDataAsset->MaxLifePoint));
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

void ATroopCharacter::GetDamage(int damagePoints) {
	LifeComponent->GetDamage(damagePoints);
	HealthBarWidgetComponent->HealthBarWidget->ChangeHealthPoints(LifeComponent->Life, LifeComponent->MaxLife);
}

