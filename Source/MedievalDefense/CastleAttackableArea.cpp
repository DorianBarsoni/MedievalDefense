#include "CastleAttackableArea.h"

ACastleAttackableArea::ACastleAttackableArea()
{
	PrimaryActorTick.bCanEverTick = true;

	LocationVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("LocationVolume"));
	RootComponent = LocationVolume;

	LocationVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACastleAttackableArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACastleAttackableArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

