#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TroopController.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API ATroopController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	ATroopController();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	UAIPerceptionComponent* AIPerceptionComponent;

	UFUNCTION(BlueprintCallable)
	void MoveTroopToLocation(FVector location, float AcceptanceRadius=0);

private:

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
