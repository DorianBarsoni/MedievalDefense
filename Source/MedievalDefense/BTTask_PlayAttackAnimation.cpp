// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PlayAttackAnimation.h"
#include "BehaviorTree/Tasks/BTTask_PlayAnimation.h"
#include "Engine/World.h"
#include "VisualLogger/VisualLogger.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "TroopController.h"
#include "TroopCharacter.h"

UBTTask_PlayAttackAnimation::UBTTask_PlayAttackAnimation(FObjectInitializer const& ObjectInitializer) {
	NodeName = "Attack Enemy";
}

EBTNodeResult::Type UBTTask_PlayAttackAnimation:: ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    if (ATroopController* const Controller = Cast<ATroopController>(OwnerComp.GetAIOwner())) {
        if (ATroopCharacter* Troop = Cast<ATroopCharacter>(Controller->GetPawn())) {
            UAnimMontage* CustomAnimation = Cast<ATroopCharacter>(Controller->GetPawn())->TroopDataAsset->AttackAnim;
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Play animation !"));
        }
    }

    return Super::ExecuteTask(OwnerComp, NodeMemory);
}