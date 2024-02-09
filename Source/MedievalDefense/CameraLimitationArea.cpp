#include "CameraLimitationArea.h"
#include "Components/BoxComponent.h"
#include "CameraPlayerPawn.h"

ACameraLimitationArea::ACameraLimitationArea()
{
	PrimaryActorTick.bCanEverTick = true;

	LocationVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("LocationVolume"));
	LocationVolume->SetGenerateOverlapEvents(true);
	RootComponent = LocationVolume;
	LocationVolume->OnComponentEndOverlap.AddDynamic(this, &ACameraLimitationArea::OnEndOverlap);

}

void ACameraLimitationArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraLimitationArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraLimitationArea::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlap ended!"));

	ACameraPlayerPawn* camera = Cast<ACameraPlayerPawn>(OtherActor);
	if (camera)
	{
		camera->SetActorLocation(camera->PreviousPosition);
	}
}

