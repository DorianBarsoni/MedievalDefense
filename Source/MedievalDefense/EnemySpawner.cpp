#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "TroopController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

UNavigationSystemBase* SpawnerNavigationSystem;
UNavigationSystemV1* SpawnerNavigationSystemV1;

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

    AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), CastleClass);
    Castle = Cast<AConstruct>(FoundActor);

    SpawnerNavigationSystem = GetWorld()->GetNavigationSystem();
    if (SpawnerNavigationSystem) {
        SpawnerNavigationSystemV1 = Cast<UNavigationSystemV1>(SpawnerNavigationSystem);
    }
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AEnemySpawner::SpawnEnemies(int NumberOfEnemiesToSpawn) {
    if (SpawnerNavigationSystemV1) {
        FNavLocation RandomLocation;
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
        for (int i = 0; i < NumberOfEnemiesToSpawn; i++) {
            if (SpawnerNavigationSystemV1->GetRandomReachablePointInRadius(GetActorLocation(), 2000.0f, RandomLocation)) {
                RandomLocation.Location += FVector(0, 0, 100);
                AActor* Enemy = GetWorld()->SpawnActor<AActor>(EnemyToSpawn, RandomLocation.Location, FRotator::ZeroRotator, SpawnParams);

                if (Enemy != nullptr) {
                    NumberOfEnemiesSpawnedLastRound++;
                    if (ATroopCharacter* Troop = Cast<ATroopCharacter>(Enemy)) {
                        if (ATroopController* TroopController = Cast<ATroopController>(Troop->GetController())) {
                            if (UBlackboardComponent* OwnBlackboard = TroopController->GetBlackboardComponent()) {
                                const FName BlackboardKeyCastle("Castle");
                                OwnBlackboard->SetValueAsObject(BlackboardKeyCastle, Castle);

                                const FName BlackboardKeyAttackablePoint("CastleAttackPoint");
                                int32 RandomAreaIndex = FMath::RandRange(0, AreasToAttack.Num() - 1);
                                ACastleAttackableArea* RandomArea = AreasToAttack[RandomAreaIndex];
                                FRotator Rotation = RandomArea->LocationVolume->GetComponentRotation();
                                FVector RandomAttackPoint = UKismetMathLibrary::RandomPointInBoundingBox(
                                    RandomArea->GetActorLocation(),
                                    RandomArea->LocationVolume->GetScaledBoxExtent().RotateAngleAxis(Rotation.Yaw, FVector::UpVector)
                                );

                                OwnBlackboard->SetValueAsVector(BlackboardKeyAttackablePoint, RandomAttackPoint);
                                //DrawDebugPoint(GetWorld(), RandomAttackPoint, 10.0f, FColor::Red, true);
                                //DrawDebugBox(GetWorld(), RandomArea->GetActorLocation(), RandomArea->LocationVolume->GetScaledBoxExtent(), FQuat(RandomArea->LocationVolume->GetComponentRotation()), FColor::Green, true);
                            }
                        }
                        if (ATroopController* TroopController = Cast<ATroopController>(Troop->GetController())) {
                            TroopController->SpawnedFrom = this;
                        }
                    }
                }
                
            } else UE_LOG(LogTemp, Error, TEXT("GetReachablePoint"));
        }  
    } else UE_LOG(LogTemp, Error, TEXT("NavSystemV1"));

    return NumberOfEnemiesSpawnedLastRound;
}

