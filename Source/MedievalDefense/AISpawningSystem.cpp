#include "AISpawningSystem.h"

AAISpawningSystem::AAISpawningSystem() {
	BestSpawner = nullptr;
}

void AAISpawningSystem::SpawnEnemies(int NumberOfEnemiesToSpawn) {
	if (BestSpawner != nullptr) {

		int NumberOfEnemiesSpawned = 0;
		for (AEnemySpawner* Spawner : EnemySpawners) {
			if (BestSpawner != Spawner) {
				int NumberOfEnemiesForCurrentSpawner = FMath::FloorToInt(Spawner->SpawningRate * NumberOfEnemiesToSpawn);
				NumberOfEnemiesSpawned += NumberOfEnemiesForCurrentSpawner;
				Spawner->SpawnEnemies(NumberOfEnemiesForCurrentSpawner);
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Spawning %d enemies"), NumberOfEnemiesForCurrentSpawner));
			}
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Spawning %d enemies"), NumberOfEnemiesToSpawn - NumberOfEnemiesSpawned));
		BestSpawner->SpawnEnemies(NumberOfEnemiesToSpawn - NumberOfEnemiesSpawned);
	}
}

void AAISpawningSystem::InitSpawningSystem() {
	if (!EnemySpawners.IsEmpty()) {
		BestSpawner = EnemySpawners[0];

		for (AEnemySpawner* Spawner : EnemySpawners) {
			Spawner->DamageDoneLastRound = 0;
			Spawner->SpawningRate = 1.0f / EnemySpawners.Num();
		}
	}
}

void AAISpawningSystem::CalculateNewSpawningRate() {
	GetBestSpawnerOfTheRound();

	if (BestSpawner != nullptr) {
		float TotalSpawnRatio = 0.0f;
		for (AEnemySpawner* Spawner : EnemySpawners) {
			if (Spawner != BestSpawner) {
				Spawner->SpawningRate /= 1.5f;
				TotalSpawnRatio += Spawner->SpawningRate;
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Spawning rate %f"), Spawner->SpawningRate));
			}
		}
		BestSpawner->SpawningRate = 1.0f - TotalSpawnRatio;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Best spawning rate %f"), BestSpawner->SpawningRate));
	}
}

void AAISpawningSystem::GetBestSpawnerOfTheRound() {
	if (!EnemySpawners.IsEmpty()) {
		BestSpawner = EnemySpawners[0];

		for (AEnemySpawner* Spawner : EnemySpawners) {
			if (Spawner->DamageDoneLastRound > BestSpawner->DamageDoneLastRound) {
				BestSpawner = Spawner;
			}
		}
	}
}