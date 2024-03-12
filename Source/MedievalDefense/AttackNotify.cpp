// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNotify.h"
#include "TroopCharacter.h"
#include "TroopController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	if (ATroopCharacter* Troop = Cast<ATroopCharacter>(MeshComp->GetOwner())) {
		if (ATroopController* TroopController = Cast<ATroopController>(Troop->GetController())) {
			if (UBlackboardComponent* OwnBlackboard = TroopController->GetBlackboardComponent()) {
				const FName BlackboardKeyEnemyRange("IsEnemyInRange");
				const FName BlackboardKeyEnemySight("IsEnemyOnSight");
				const FName BlackboardKeyChased("EnemyChased");
				const FName BlackboardKeyCastleRange("IsCastleInRange");
				const FName BlackboardKeyCastle("Castle");

				ATroopCharacter* EnemyChased = Cast<ATroopCharacter>(OwnBlackboard->GetValueAsObject(BlackboardKeyChased));

				if (EnemyChased) {
					EnemyChased->GetDamage(Troop->TroopDataAsset->AttackDamage);

					if (EnemyChased->IsDead()) {
						if (ATroopController* EnemyController = Cast<ATroopController>(EnemyChased->GetController())) {
							if (UBlackboardComponent* EnemyBlackboard = EnemyController->GetBlackboardComponent()) {
								const FName BlackboardKeyEnemyIsDead("IsDead");
								EnemyBlackboard->SetValueAsBool(BlackboardKeyEnemyIsDead, true);
							}
						}

						TroopController->SwitchToNextEnemy();
					}
				}
				else if (false) {
					//Si il y a chateau et qu'on est dans la range attaquer le chateau
				}

			}
		}
	}
}