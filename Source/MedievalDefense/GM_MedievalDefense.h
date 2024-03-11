#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemySpawner.h"
#include "GM_MedievalDefense.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateTimerDelegate, int32, Seconds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateRoundDelegate, int32, RoundNumber);


UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API AGM_MedievalDefense : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGM_MedievalDefense();

	int RoundNumber;
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PreparationTime = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfEnemiesToAdd = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentAmoutOfEnemies = 0;

	UPROPERTY(BlueprintAssignable, Category = "Timer")
	FUpdateTimerDelegate UpdateTimer;

	UPROPERTY(BlueprintAssignable, Category = "Round")
	FUpdateRoundDelegate UpdateRound;

	virtual void BeginPlay() override;

private:
	TArray<AEnemySpawner*> EnemySpawners;

	void TimerFunction();

	void SpawnEnemies();

	void EndPlay(const EEndPlayReason::Type EndPlayReason);
};
