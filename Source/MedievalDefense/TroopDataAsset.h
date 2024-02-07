// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TroopDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API UTroopDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float SpeedMovement;

	UPROPERTY(EditAnywhere)
	int LifePoint;

	UPROPERTY(EditAnywhere)
	int AttackDamage;

	UPROPERTY(EditAnywhere)
	float Cooldown;
	
};
