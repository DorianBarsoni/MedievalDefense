#include "Construct.h"
#include "Kismet/GameplayStatics.h"
#include "GM_MedievalDefense.h"

AConstruct::AConstruct() {
	PrimaryActorTick.bCanEverTick = true;
	LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));
	HealthComponentWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
}

void AConstruct::BeginPlay() {
	Super::BeginPlay();

	if (LifeComponent) {
		LifeComponent->Life = ConstructDataAsset->LifePoints;
		LifeComponent->MaxLife = ConstructDataAsset->MaxLifePoints;
	} else UE_LOG(LogTemp, Error, TEXT("LifeComponent is not valid in AConstruct::BeginPlay"));

	if (HealthComponentWidget) {
		WidgetAsHealthBar = Cast<UHealthBar>(HealthComponentWidget->GetWidget());
		WidgetAsHealthBar->ChangeHealthPoints(ConstructDataAsset->LifePoints, ConstructDataAsset->MaxLifePoints);
	} else UE_LOG(LogTemp, Error, TEXT("HealthComponentWidget error"));	
}

void AConstruct::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AConstruct::GetDamage(int damagePoints) {
	LifeComponent->GetDamage(damagePoints);
	WidgetAsHealthBar->ChangeHealthPoints(LifeComponent->Life, LifeComponent->MaxLife);

	if (IsDead()) {
		if (AGM_MedievalDefense* GMMedieval = Cast<AGM_MedievalDefense>(UGameplayStatics::GetGameMode(GetWorld()))) {
			GMMedieval->Defeat();
		}
	}
}

bool AConstruct::IsDead() {
	return LifeComponent->Life <= 0;
}

