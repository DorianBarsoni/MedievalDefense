#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "TroopController.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API ATroopController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	ATroopController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Component")
	UAIPerceptionComponent* AIPerceptionComponent;

	UFUNCTION(BlueprintCallable)
	void MoveTroopToLocation(FVector location);

private:

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
