// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_PlayAnimation.h"
#include "BTTask_PlayAttackAnimation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API UBTTask_PlayAttackAnimation : public UBTTask_PlayAnimation
{
	GENERATED_BODY()

public:
	explicit UBTTask_PlayAttackAnimation(FObjectInitializer const& ObjectInitializer);
	void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);
};
