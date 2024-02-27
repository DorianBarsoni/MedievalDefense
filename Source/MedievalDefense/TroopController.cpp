#include "TroopController.h"
#include "TroopCharacter.h"


ATroopController::ATroopController() {
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 200.0f;
	SightConfig->LoseSightRadius = 200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 360.0f;

	FAISenseAffiliationFilter SenseAffiliationFilter;
	SenseAffiliationFilter.bDetectEnemies = true;
	SenseAffiliationFilter.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation = SenseAffiliationFilter;
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATroopController::OnTargetPerceptionUpdated);

	AIPerceptionComponent->ConfigureSense(*SightConfig);
}

void ATroopController::BeginPlay() {
	Super::BeginPlay();

}

void ATroopController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (ATroopCharacter* Troop = Cast<ATroopCharacter>(InPawn)) {
		SightConfig->SightRadius = Troop->TroopDataAsset->Range;
		SightConfig->LoseSightRadius = Troop->TroopDataAsset->Range;

		AIPerceptionComponent->ConfigureSense(*SightConfig);
	}
	
}

void ATroopController::MoveTroopToLocation(FVector location) {
	this->MoveToLocation(location);
}

void ATroopController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) {
	if (Stimulus.WasSuccessfullySensed() && Stimulus.Strength > 0.0f) {
		if (Stimulus.StimulusLocation != FVector::ZeroVector) {
			//float DistanceToActor = FVector::Distance(GetPawn()->GetActorLocation(), Stimulus.StimulusLocation);

			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Actor!"));
		}
	}
}

