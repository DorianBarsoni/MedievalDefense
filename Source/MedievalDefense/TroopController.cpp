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
		ConfigSight->LoseSightRadius = Troop->TroopDataAsset->AttackRange;
		AIPerceptionComponentForAttack->RequestStimuliListenerUpdate();


		Config = AIPerceptionComponentForSight->GetSenseConfig(Id);
		ConfigSight = Cast<UAISenseConfig_Sight>(Config);
		ConfigSight->SightRadius = Troop->TroopDataAsset->SightRange;
		ConfigSight->LoseSightRadius = Troop->TroopDataAsset->SightRange;
		AIPerceptionComponentForSight->RequestStimuliListenerUpdate();
	}
}

void ATroopController::MoveTroopToLocation(FVector location, float AcceptanceRadius) {
	this->MoveToLocation(location, AcceptanceRadius);
}

void ATroopController::OnTargetPerceptionUpdatedAttack(AActor* Actor, FAIStimulus Stimulus) {
	if (Stimulus.WasSuccessfullySensed() && Stimulus.Strength > 0.0f) {
		if (Stimulus.StimulusLocation != FVector::ZeroVector) {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Attack Range"));
		}
	}
}

void ATroopController::OnTargetPerceptionUpdatedSight(AActor* Actor, FAIStimulus Stimulus) {
			if (ATroopCharacter* Troop = Cast<ATroopCharacter>(Actor)) {
				FName ActorTag = Troop->TroopDataAsset->TeamTag.GetTagName();
				FName OwnTag = Cast<ATroopCharacter>(GetPawn())->TroopDataAsset->TeamTag.GetTagName();
				if (OwnTag != ActorTag) {
					UBlackboardComponent* OwnBlackboard = GetBlackboardComponent();
					if (OwnBlackboard) {
						const FName BlackboardKey("IsEnemyOnSight");

						if (Stimulus.WasSuccessfullySensed()) {
							OwnBlackboard->SetValueAsBool(BlackboardKey, true);
							GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Entrée SightRange"));
						}
						else {
							OwnBlackboard->SetValueAsBool(BlackboardKey, false);
							GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Sortie SightRange"));
						}
					}
				}
			}
}

