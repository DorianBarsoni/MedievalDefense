// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TroopCharacter.h"
#include "KnightDataAsset.h"
#include "LifeComponent.h"
#include "KnightCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API AKnightCharacter : public ATroopCharacter
{
	GENERATED_BODY()

public:
	AKnightCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UKnightDataAsset *KnightDataAsset;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
