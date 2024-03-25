// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemySpawner.h"
#include "AISpawningSystem.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDEFENSE_API AAISpawningSystem : public AActor
{
	GENERATED_BODY()

public:
	TArray<AEnemySpawner*> EnemySpawners;

	AEnemySpawner* BestSpawner;

	AAISpawningSystem();

	void SpawnEnemies(int NumberOfEnemiesToSpawn);

	void InitSpawningSystem();

	void CalculateNewSpawningRate();

private:
	void GetBestSpawnerOfTheRound();
	
};
