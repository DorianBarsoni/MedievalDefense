#include "KnightCharacter.h"

AKnightCharacter::AKnightCharacter() {
}

void AKnightCharacter::BeginPlay() {
	LifeComponent->SetLife(TroopDataAsset->LifePoint);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Life : %d"), LifeComponent->GetLife()));
}

void AKnightCharacter::Tick(float DeltaTime) {

}