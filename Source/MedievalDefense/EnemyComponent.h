// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TeamComponent.h"
#include "EnemyComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API UEnemyComponent : public UTeamComponent
{
	GENERATED_BODY()
	
public:
	UEnemyComponent();
};
