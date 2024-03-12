#include "TroopCharacter.h"
#include "HealthBar.h"
#include "GameFramework/CharacterMovementComponent.h"

ATroopCharacter::ATroopCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));
	TroopDataAsset = CreateDefaultSubobject<UTroopDataAsset>(TEXT("TroopDataAsset"));
	HealthComponentWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
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

	if (HealthComponentWidget) {
		HealthComponentWidget->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		WidgetAsHealthBar = Cast<UHealthBar>(HealthComponentWidget->GetWidget());
		WidgetAsHealthBar->ChangeHealthPoints(TroopDataAsset->LifePoint, TroopDataAsset->MaxLifePoint);
		if (TroopDataAsset->TeamTag.GetTagName() == "Enemy") {
			WidgetAsHealthBar->HealthBar->SetVisibility(ESlateVisibility::Visible);
		} else WidgetAsHealthBar->HealthBar->SetVisibility(ESlateVisibility::Hidden);
	} else UE_LOG(LogTemp, Error, TEXT("HealthComponentWidget error"));
}

void ATroopCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATroopCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATroopCharacter::GetDamage(int damagePoints) {
	LifeComponent->GetDamage(damagePoints);
	WidgetAsHealthBar->ChangeHealthPoints(LifeComponent->Life, LifeComponent->MaxLife);
}

bool ATroopCharacter::IsDead() {
	return LifeComponent->Life <= 0;
}

