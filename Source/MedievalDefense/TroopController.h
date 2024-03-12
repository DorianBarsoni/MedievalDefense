#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "TroopCharacter.h"
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
	UAIPerceptionComponent* AIPerceptionComponentForAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UAIPerceptionComponent* AIPerceptionComponentForSight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATroopCharacter*> EnemiesToAttack;

	UFUNCTION(BlueprintCallable)
	void MoveTroopToLocation(FVector location, float AcceptanceRadius=0);

	void SwitchToNextEnemy();

private:
	UFUNCTION()
	void OnTargetPerceptionUpdatedAttack(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetPerceptionUpdatedSight(AActor* Actor, FAIStimulus Stimulus);
};
