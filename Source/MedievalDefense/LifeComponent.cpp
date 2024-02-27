#include "LifeComponent.h"

ULifeComponent::ULifeComponent() : Life(0), MaxLife(0) {
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULifeComponent::BeginPlay() {
	Super::BeginPlay();
	
}


// Called every frame
void ULifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULifeComponent::GetDamage(int damagePoints) {
	if(Life > 0)
		Life -= damagePoints;
}

