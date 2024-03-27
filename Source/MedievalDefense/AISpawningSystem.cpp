#include "AISpawningSystem.h"

AAISpawningSystem::AAISpawningSystem() {
	BestSpawner = nullptr;
}

int AAISpawningSystem::SpawnEnemies(int NumberOfEnemiesToSpawn) {
	int TotalOfEnnemiesSpawned = 0;

	if (BestSpawner != nullptr) {

		int NumberOfEnemiesSpawned = 0;

		for (AEnemySpawner* Spawner : EnemySpawners) {
			if (BestSpawner != Spawner) {
				int NumberOfEnemiesForCurrentSpawner = FMath::FloorToInt(Spawner->SpawningRate * NumberOfEnemiesToSpawn);
				NumberOfEnemiesSpawned += NumberOfEnemiesForCurrentSpawner;
				TotalOfEnnemiesSpawned += Spawner->SpawnEnemies(NumberOfEnemiesForCurrentSpawner);
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Spawning %d enemies"), NumberOfEnemiesForCurrentSpawner));
			}
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Spawning %d enemies"), NumberOfEnemiesToSpawn - NumberOfEnemiesSpawned));
		TotalOfEnnemiesSpawned += BestSpawner->SpawnEnemies(NumberOfEnemiesToSpawn - NumberOfEnemiesSpawned);
	}

	return TotalOfEnnemiesSpawned;
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
				Spawner->NumberOfEnemiesSpawnedLastRound = 0;
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Spawning rate %f"), Spawner->SpawningRate));
			}
		}
		BestSpawner->SpawningRate = 1.0f - TotalSpawnRatio;
		BestSpawner->NumberOfEnemiesSpawnedLastRound = 0;
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Best spawning rate %f"), BestSpawner->SpawningRate));
	}
}

void AAISpawningSystem::GetBestSpawnerOfTheRound() {
	if (!EnemySpawners.IsEmpty()) {
		BestSpawner = EnemySpawners[0];

		for (AEnemySpawner* Spawner : EnemySpawners) {
			float EnemySpawnedBySpawner = static_cast<float>(Spawner->NumberOfEnemiesSpawnedLastRound);
			float EnemiesSpawnedByBestSpawner = static_cast<float>(BestSpawner->NumberOfEnemiesSpawnedLastRound);

			if (EnemiesSpawnedByBestSpawner == 0) {
				BestSpawner = Spawner;
			}
			else if (EnemySpawnedBySpawner != 0) {
				if (Spawner->DamageDoneLastRound / EnemySpawnedBySpawner > BestSpawner->DamageDoneLastRound / EnemiesSpawnedByBestSpawner) {
					BestSpawner = Spawner;
				}
			}
		}
	}
}