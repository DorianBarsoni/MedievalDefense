// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MedievalDefense.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"


AGM_MedievalDefense::AGM_MedievalDefense()
{
	RoundNumber = 0;
	PreparationTime = 60;
}


void AGM_MedievalDefense::BeginPlay() {
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors) {
		AEnemySpawner* EnemySpawner = Cast<AEnemySpawner>(Actor);
		if (EnemySpawner) {
			EnemySpawners.Add(EnemySpawner);
		}
	}
	NumberOfEnemiesCurrentlyAlive = 10;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGM_MedievalDefense::TimerFunction, 1.0f, true, 1.0f);
}

void AGM_MedievalDefense::TimerFunction()
{
	UpdateTimer.Broadcast(PreparationTime);

	if (PreparationTime <= 0) {
		PreparationTime = 60;
		CurrentAmoutOfEnemies += NumberOfEnemiesToAdd;
		RoundNumber++;
		GetWorldTimerManager().ClearTimer(TimerHandle);
		UpdateRound.Broadcast(RoundNumber);
		
		SpawnEnemies();
	}
	PreparationTime--;
}

void AGM_MedievalDefense::SpawnEnemies() {
	int NumberOfEnemiesToSpawn = CurrentAmoutOfEnemies;
	int NumberOfEnemiesPerSpawner = CurrentAmoutOfEnemies / EnemySpawners.Num();

	int i;
	for (i=0; i < EnemySpawners.Num() - 1; i++) {
		EnemySpawners[i]->SpawnEnemies(NumberOfEnemiesPerSpawner);
	}
	EnemySpawners[i]->SpawnEnemies(NumberOfEnemiesPerSpawner + CurrentAmoutOfEnemies % EnemySpawners.Num());
}

void AGM_MedievalDefense::EnemyKilled() {
	if (--NumberOfEnemiesCurrentlyAlive <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "FINI");
	}
}

void AGM_MedievalDefense::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(TimerHandle);

	Super::EndPlay(EndPlayReason);
}

