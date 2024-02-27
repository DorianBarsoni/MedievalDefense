// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI.h"
#include "NavigationSystem.h"

void UPlayerUI::onKnightButtonClicked(FVector SpawnPoint) {
    if (KnightActor) {         
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

        AActor* NewTroopCharacter = GetWorld()->SpawnActor<AActor>(KnightActor, getSpawnPoint(SpawnPoint), FRotator::ZeroRotator, SpawnParams);
    } else {
        UE_LOG(LogTemp, Error, TEXT("TroopCharacterBlueprint not set in UPlayerUI"));
    }
}

void UPlayerUI::onArcherButtonClicked(FVector SpawnPoint) {
    if (ArcherActor) {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        AActor* NewTroopCharacter = GetWorld()->SpawnActor<AActor>(ArcherActor, getSpawnPoint(SpawnPoint), FRotator::ZeroRotator, SpawnParams);
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("TroopCharacterBlueprint not set in UPlayerUI"));
    }
}

FVector UPlayerUI::getSpawnPoint(FVector SpawnPoint) {
    UNavigationSystemBase* NavigationSystem = GetWorld()->GetNavigationSystem();
    if (NavigationSystem) {
        UNavigationSystemV1* NavigationSystemV1 = Cast<UNavigationSystemV1>(NavigationSystem);
        if (NavigationSystemV1) {
            FNavLocation RandomLocation;
            if (NavigationSystemV1->GetRandomReachablePointInRadius(SpawnPoint, SpawnRadius, RandomLocation)) {
                return RandomLocation.Location + FVector(0, 0, 100);
            } else { UE_LOG(LogTemp, Error, TEXT("GetReachablePoint")); }
        } else { UE_LOG(LogTemp, Error, TEXT("NavSystemV1")); }
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("NavSystem"));
    }

    return SpawnPoint;
}