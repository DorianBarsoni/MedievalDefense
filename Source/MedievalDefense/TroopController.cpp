#include "TroopController.h"
#include "TroopCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"



ATroopController::ATroopController() {
	AIPerceptionComponentForAttack = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponentForAttack"));
	AIPerceptionComponentForSight = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponentForSight"));
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	UAISenseConfig_Sight* SightConfig2 = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig2"));

	SightConfig->SightRadius = 200.0f;
	SightConfig->LoseSightRadius = 200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 360.0f;

	FAISenseAffiliationFilter SenseAffiliationFilter;
	SenseAffiliationFilter.bDetectEnemies = true;
	SenseAffiliationFilter.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation = SenseAffiliationFilter;
	AIPerceptionComponentForAttack->OnTargetPerceptionUpdated.AddDynamic(this, &ATroopController::OnTargetPerceptionUpdatedAttack);

	AIPerceptionComponentForAttack->ConfigureSense(*SightConfig);

	SightConfig2->SightRadius = 1000.0f;
	SightConfig2->LoseSightRadius = 1000.0f;
	SightConfig2->PeripheralVisionAngleDegrees = 360.0f;
	SightConfig2->DetectionByAffiliation = SenseAffiliationFilter;
	AIPerceptionComponentForSight->OnTargetPerceptionUpdated.AddDynamic(this, &ATroopController::OnTargetPerceptionUpdatedSight);
	AIPerceptionComponentForSight->ConfigureSense(*SightConfig2);
}

void ATroopController::BeginPlay() {
	Super::BeginPlay();

}

void ATroopController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (ATroopCharacter* Troop = Cast<ATroopCharacter>(InPawn)) {
		FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());
		UAISenseConfig* Config = AIPerceptionComponentForAttack->GetSenseConfig(Id);
		UAISenseConfig_Sight* ConfigSight = Cast<UAISenseConfig_Sight>(Config);

		ConfigSight->SightRadius = Troop->TroopDataAsset->AttackRange;
		ConfigSight->LoseSightRadius = Troop->TroopDataAsset->AttackRange+20;
		AIPerceptionComponentForAttack->RequestStimuliListenerUpdate();


		Config = AIPerceptionComponentForSight->GetSenseConfig(Id);
		ConfigSight = Cast<UAISenseConfig_Sight>(Config);
		ConfigSight->SightRadius = Troop->TroopDataAsset->SightRange;
		ConfigSight->LoseSightRadius = Troop->TroopDataAsset->LoseSightRange;
		AIPerceptionComponentForSight->RequestStimuliListenerUpdate();
	}
}

void ATroopController::MoveTroopToLocation(FVector location, float AcceptanceRadius) {
	this->MoveToLocation(location, AcceptanceRadius);
}

void ATroopController::SwitchToNextEnemy() {
	//Si attack pas vide on cherche le prochain dans attack
	//sinon si move pas vide chercher le prochain dans move
	//sinon on passe les bool à false et enemy to attack à nullptr

	UBlackboardComponent* OwnBlackboard = GetBlackboardComponent();
	const FName BlackboardKeyChased("EnemyChased");
	const FName BlackboardKeyEnemyRange("IsEnemyInRange");
	const FName BlackboardKeyEnemySight("IsEnemyOnSight");

	for (int32 Index = 0; Index < EnemiesToAttack.Num(); ++Index) {
		auto EnemyToAttack = EnemiesToAttack[Index];
		if (EnemyToAttack->IsDead()) {
			EnemiesToAttack.RemoveAt(Index);
			Index--;
		}
	}

	if (!EnemiesToAttack.IsEmpty()) {
		OwnBlackboard->SetValueAsObject(BlackboardKeyChased, EnemiesToAttack[0]);
		OwnBlackboard->SetValueAsBool(BlackboardKeyEnemyRange, true);
		OwnBlackboard->SetValueAsBool(BlackboardKeyEnemySight, true);
	} else {
		OwnBlackboard->SetValueAsBool(BlackboardKeyEnemyRange, false);

		for (int32 Index = 0; Index < EnemiesInRange.Num(); ++Index) {
			auto EnemyInRange = EnemiesInRange[Index];
			if (EnemyInRange->IsDead()) {
				EnemiesInRange.RemoveAt(Index);
				Index--;
			}
		}

		if (!EnemiesInRange.IsEmpty()) {
			OwnBlackboard->SetValueAsObject(BlackboardKeyChased, EnemiesInRange[0]);
			OwnBlackboard->SetValueAsBool(BlackboardKeyEnemySight, true);
		} else {
			OwnBlackboard->SetValueAsObject(BlackboardKeyChased, nullptr);
			OwnBlackboard->SetValueAsBool(BlackboardKeyEnemySight, false);
		}
	}
}

void ATroopController::OnTargetPerceptionUpdatedAttack(AActor* Actor, FAIStimulus Stimulus) {
	if (ATroopCharacter* Troop = Cast<ATroopCharacter>(Actor)) {
		FName ActorTag = Troop->TroopDataAsset->TeamTag.GetTagName();
		ATroopCharacter* OwnTroop = Cast<ATroopCharacter>(GetPawn());
		FName OwnTag = OwnTroop->TroopDataAsset->TeamTag.GetTagName();
		if (OwnTag != ActorTag) {
			UBlackboardComponent* OwnBlackboard = GetBlackboardComponent();
			if (OwnBlackboard) {
				const FName BlackboardKeyRange("IsEnemyInRange");

				bool bIsCurrentlyInsideRadius = FVector::DistSquared(Troop->GetActorLocation(), GetPawn()->GetActorLocation())
					<= OwnTroop->TroopDataAsset->AttackRange * OwnTroop->TroopDataAsset->AttackRange;

				if (bIsCurrentlyInsideRadius) {
					EnemiesToAttack.Add(Troop);
					OwnBlackboard->SetValueAsBool(BlackboardKeyRange, true);
				}
				else {
					EnemiesToAttack.Remove(Troop);
					OwnBlackboard->SetValueAsBool(BlackboardKeyRange, false);
				}
			}
		}
	}
}

void ATroopController::OnTargetPerceptionUpdatedSight(AActor* Actor, FAIStimulus Stimulus) {
	if (ATroopCharacter* Troop = Cast<ATroopCharacter>(Actor)) {
		FName ActorTag = Troop->TroopDataAsset->TeamTag.GetTagName();
		ATroopCharacter* OwnTroop = Cast<ATroopCharacter>(GetPawn());
		FName OwnTag = OwnTroop->TroopDataAsset->TeamTag.GetTagName();
		if (OwnTag != ActorTag) {
			UBlackboardComponent* OwnBlackboard = GetBlackboardComponent();
			if (OwnBlackboard) {
				const FName BlackboardKeySight("IsEnemyOnSight");
				const FName BlackboardKeyChased("EnemyChased");

				bool bIsCurrentlyInsideRadius = FVector::DistSquared(Troop->GetActorLocation(), GetPawn()->GetActorLocation())
					<= OwnTroop->TroopDataAsset->SightRange * OwnTroop->TroopDataAsset->SightRange;

				if (bIsCurrentlyInsideRadius) {
					EnemiesInRange.Add(Troop);
					OwnBlackboard->SetValueAsBool(BlackboardKeySight, true);
					if (EnemiesInRange.Num() == 1) {
						OwnBlackboard->SetValueAsObject(BlackboardKeyChased, EnemiesInRange[0]);
					}
				} else {
					EnemiesInRange.Remove(Troop);
					OwnBlackboard->SetValueAsBool(BlackboardKeySight, false);
					OwnBlackboard->SetValueAsObject(BlackboardKeyChased, nullptr);
				}
			}
		}
	}
}

