#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraPlayerController.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API ACameraPlayerController : public APlayerController
{
	GENERATED_BODY()

	FRotator Rotation;
	FVector ForwardVector;
	FVector RightVector;

	ACameraPlayerController();

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};
