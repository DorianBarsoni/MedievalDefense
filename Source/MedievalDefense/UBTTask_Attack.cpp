// UBTTask_Attack.cpp
#include "UBTTask_Attack.h"
#include "TroopCharacter.h"
#include "TroopController.h"

UUBTTask_Attack::UUBTTask_Attack(FObjectInitializer const& ObjectInitializer) {
    NodeName = "Attack Enemy";
}

EBTNodeResult::Type UUBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& InOwnerComp, uint8* NodeMemory) {
    if (ATroopController* const Controller = Cast<ATroopController>(InOwnerComp.GetAIOwner())) {
        if (ATroopCharacter* Troop = Cast<ATroopCharacter>(Controller->GetPawn())) {
            Troop->PlayAnimMontage(Troop->TroopDataAsset->AttackAnim);

            return EBTNodeResult::Succeeded;
        }
    }
    return EBTNodeResult::Failed;
}
