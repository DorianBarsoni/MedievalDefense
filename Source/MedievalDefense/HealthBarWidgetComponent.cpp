#include "HealthBarWidgetComponent.h"

UHealthBarWidgetComponent::UHealthBarWidgetComponent() {
}

void UHealthBarWidgetComponent::BeginPlay() {
	Super::BeginPlay();

	HealthBarWidget = CreateWidget<UHealthBar>(GetWorld(), HealthWidgetTemplate, FName("HealthBarWidget"));
	SetWidgetClass(HealthWidgetTemplate);
}

void UHealthBarWidgetComponent::ChangeHealthPoints(int healthPoints, int maxHealth) {
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Component : %d %d"), healthPoints, maxHealth));
	
	HealthBarWidget->ChangeHealthPoints(healthPoints, maxHealth);
}
