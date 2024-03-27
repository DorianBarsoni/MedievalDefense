#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CastleAttackableArea.h"
#include "TroopCharacter.h"
#include "Construct.h"
#include "EnemySpawner.generated.h"

UCLASS()
class MEDIEVALDEFENSE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACastleAttackableArea> AreasToAttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATroopCharacter> EnemyToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AConstruct> CastleClass;

	TArray<ACastleAttackableArea*> AreasToAttack;

	int DamageDoneLastRound = 0;

	float SpawningRate = 0.0f;

	int NumberOfEnemiesSpawnedLastRound = 0;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int SpawnEnemies(int NumberOfEnemiesToSpawn);

private:
	AConstruct* Castle;
};
