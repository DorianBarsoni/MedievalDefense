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

void UBTTask_PlayAttackAnimation::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

    if (ATroopController* const Controller = Cast<ATroopController>(OwnerComp.GetAIOwner())) {
        if (ATroopCharacter* Troop = Cast<ATroopCharacter>(Controller->GetPawn())) {
            UAnimMontage* CustomAnimation = Cast<ATroopCharacter>(Controller->GetPawn())->TroopDataAsset->AttackAnim;

            if (TaskResult == EBTNodeResult::Succeeded && CustomAnimation)
            {
                // Obtient le pawn du contrôleur AI
                UAnimInstance* AnimInstance = Troop->GetMesh()->GetAnimInstance();
                if (AnimInstance)
                {
                    // Joue l'animation personnalisée
                    AnimInstance->Montage_Play(CustomAnimation, 1.f);
                }
            }
        }
    }
}
