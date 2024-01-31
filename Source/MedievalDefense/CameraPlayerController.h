// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API ACameraPlayerController : public APlayerController
{
	GENERATED_BODY()

	ACameraPlayerController();

public:
	UPROPERTY(EditAnywhere)
	int minX;
	UPROPERTY(EditAnywhere)
	int maxX;
	UPROPERTY(EditAnywhere)
	int minY;
	UPROPERTY(EditAnywhere)
	int maxY;
	UPROPERTY(EditAnywhere)
	int speed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
