#include "TroopController.h"
#include "TroopCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"



ATroopController::ATroopController() {
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

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
		FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());
		UAISenseConfig* Config = AIPerceptionComponent->GetSenseConfig(Id);
		UAISenseConfig_Sight* ConfigSight = Cast<UAISenseConfig_Sight>(Config);

		ConfigSight->SightRadius = Troop->TroopDataAsset->Range;
		ConfigSight->LoseSightRadius = Troop->TroopDataAsset->Range;

		AIPerceptionComponent->RequestStimuliListenerUpdate();
	}
}

void ATroopController::MoveTroopToLocation(FVector location, float AcceptanceRadius) {

	this->MoveToLocation(location, AcceptanceRadius);
	/*FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(location);

	FPathFollowingRequestResult MoveResult;
	MoveResult = MoveTo(MoveRequest, nullptr);

	if (MoveResult.Code == EPathFollowingRequestResult::RequestSuccessful) {
		UE_LOG(LogTemp, Warning, TEXT("Déplacement initié avec succès."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Échec du déplacement."));
	}*/
}

void ATroopController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) {
	if (Stimulus.WasSuccessfullySensed() && Stimulus.Strength > 0.0f) {
		if (Stimulus.StimulusLocation != FVector::ZeroVector) {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, TEXT("Actor!"));
		}
	}
}

