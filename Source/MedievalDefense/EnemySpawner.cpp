#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "TroopController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

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
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemies(int NumberOfEnemiesToSpawn) {
    UNavigationSystemBase* NavigationSystem = GetWorld()->GetNavigationSystem();
    if (NavigationSystem) {
        UNavigationSystemV1* NavigationSystemV1 = Cast<UNavigationSystemV1>(NavigationSystem);
        if (NavigationSystemV1) {
            FNavLocation RandomLocation;
            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
            for (int i = 0; i < NumberOfEnemiesToSpawn; i++) {
                if (NavigationSystemV1->GetRandomReachablePointInRadius(GetActorLocation(), 3000.0f, RandomLocation)) {
                    RandomLocation.Location += FVector(0, 0, 100);
                    AActor* Enemy = GetWorld()->SpawnActor<AActor>(EnemyToSpawn, RandomLocation.Location, FRotator::ZeroRotator, SpawnParams);

                    if (ATroopCharacter* Troop = Cast<ATroopCharacter>(Enemy)) {
                        if (ATroopController* TroopController = Cast<ATroopController>(Troop->GetController())) {
                            if (UBlackboardComponent* OwnBlackboard = TroopController->GetBlackboardComponent()) {
                                const FName BlackboardKeyCastle("Castle");
                                OwnBlackboard->SetValueAsObject(BlackboardKeyCastle, Castle);

                                const FName BlackboardKeyAttackablePoint("CastleAttackPoint");
                                int32 RandomAreaIndex = FMath::RandRange(0, AreasToAttack.Num() - 1);
                                ACastleAttackableArea* RandomArea = AreasToAttack[RandomAreaIndex];
                                FVector RandomAttackPoint = UKismetMathLibrary::RandomPointInBoundingBox(RandomArea->GetActorLocation(), RandomArea->LocationVolume->GetComponentScale());
                                OwnBlackboard->SetValueAsVector(BlackboardKeyAttackablePoint, RandomAttackPoint);
                            }
                        }
                    }
                }
                else { UE_LOG(LogTemp, Error, TEXT("GetReachablePoint")); }
            }   
        }
        else { UE_LOG(LogTemp, Error, TEXT("NavSystemV1")); }
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("NavSystem"));
    }
}

