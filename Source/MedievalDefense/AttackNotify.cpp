// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNotify.h"
#include "TroopCharacter.h"
#include "TroopController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Construct.h"

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
				if (EnemyChased && OwnBlackboard->GetValueAsBool(BlackboardKeyEnemyRange)) {
					EnemyChased->GetDamage(Troop->TroopDataAsset->AttackDamage);

					if (EnemyChased->IsDead()) {
						if (ATroopController* EnemyController = Cast<ATroopController>(EnemyChased->GetController())) {
							if (UBlackboardComponent* EnemyBlackboard = EnemyController->GetBlackboardComponent()) {
								const FName BlackboardKeyEnemyIsDead("IsDead");
								EnemyBlackboard->SetValueAsBool(BlackboardKeyEnemyIsDead, true);
							}
						}
						TroopController->EnemiesInRange.Remove(EnemyChased);
						TroopController->EnemiesToAttack.Remove(EnemyChased);
						TroopController->SwitchToNextEnemy();
					}
				}
				else if (AConstruct* Castle = Cast<AConstruct>(OwnBlackboard->GetValueAsObject(BlackboardKeyCastle))) {
					if (Troop->TroopDataAsset->TeamTag.GetTagName() == "Ally") {
						if (Castle == nullptr) {
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("nullptr"));
						}
						else GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("valid"));
					}
					
					if (OwnBlackboard->GetValueAsBool(BlackboardKeyCastleRange)) {
						if (!Castle->IsDead()) {
							Castle->GetDamage(Troop->TroopDataAsset->AttackDamage);
						}
					}
				}

			}
		}
	}
}