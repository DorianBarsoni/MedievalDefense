#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AreasToAttackType, FoundActors);

	for (AActor* FoundActor : FoundActors) {
		AreasToAttack.Add(Cast<ACastleAttackableArea>(FoundActor));
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString::Printf(TEXT("%d spawners"), AreasToAttack.Num()));
	
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy() {
    UNavigationSystemBase* NavigationSystem = GetWorld()->GetNavigationSystem();
    if (NavigationSystem) {
        UNavigationSystemV1* NavigationSystemV1 = Cast<UNavigationSystemV1>(NavigationSystem);
        if (NavigationSystemV1) {
            FNavLocation RandomLocation;
            if (NavigationSystemV1->GetRandomReachablePointInRadius(GetActorLocation(), 3000.0f, RandomLocation)) {
                RandomLocation.Location += FVector(0, 0, 100);
                FActorSpawnParameters SpawnParams;
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
                GetWorld()->SpawnActor<AActor>(EnemyToSpawn, RandomLocation.Location, FRotator::ZeroRotator, SpawnParams);
            }
            else { UE_LOG(LogTemp, Error, TEXT("GetReachablePoint")); }
        }
        else { UE_LOG(LogTemp, Error, TEXT("NavSystemV1")); }
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("NavSystem"));
    }
}

