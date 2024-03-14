// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI.h"
#include "NavigationSystem.h"
#include "GM_MedievalDefense.h"
#include "PlayerInventorySubsystem.h"

FActorSpawnParameters SpawnParams;

void UPlayerUI::NativeConstruct() {
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

    Super::NativeConstruct();

    AGM_MedievalDefense* GameMode = GetWorld()->GetAuthGameMode<AGM_MedievalDefense>();
    if (GameMode) {
        TimeBeforeNextRound->SetText(FText::FromString(FString::Printf(TEXT("%d"), GameMode->PreparationTime)));
        CurrentRound->SetText(FText::FromString(FString::Printf(TEXT("%d"), GameMode->RoundNumber)));

        GameMode->UpdateTimer.AddDynamic(this, &UPlayerUI::UpdateTimeBeforeNextRound);
        GameMode->UpdateRound.AddDynamic(this, &UPlayerUI::UpdateRound);
    }
}

bool UPlayerUI::onKnightButtonClicked(FVector SpawnPoint) {
    if (APlayerController* OwningPlayerController = GetOwningPlayer()) {
        if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(OwningPlayerController->Player)) {
            if (UPlayerInventorySubsystem* InventorySubsystem = LocalPlayer->GetSubsystem<UPlayerInventorySubsystem>()) {
                if (InventorySubsystem->NumberOfKnightInvocable > 0) {
                    if (SpawnSpecificActor(SpawnPoint, KnightActor)) {
                        UpdateKnightNumber(--InventorySubsystem->NumberOfKnightInvocable);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool UPlayerUI::onArcherButtonClicked(FVector SpawnPoint) {
    if (APlayerController* OwningPlayerController = GetOwningPlayer()) {
        if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(OwningPlayerController->Player)) {
            if (UPlayerInventorySubsystem* InventorySubsystem = LocalPlayer->GetSubsystem<UPlayerInventorySubsystem>()) {
                if (InventorySubsystem->NumberOfArcherInvocable > 0) {
                    if (SpawnSpecificActor(SpawnPoint, ArcherActor)) {
                        UpdateArcherNumber(--InventorySubsystem->NumberOfArcherInvocable);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool UPlayerUI::SpawnSpecificActor(FVector SpawnPoint, UClass *ActorClassToSpawn) {
    if (ActorClassToSpawn) {
        GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, getSpawnPoint(SpawnPoint), FRotator::ZeroRotator, SpawnParams);
        return true;
    }
    UE_LOG(LogTemp, Error, TEXT("TroopCharacterBlueprint not set in UPlayerUI"));
    return false;
}

void UPlayerUI::UpdateTimeBeforeNextRound(int32 Seconds)
{
    if (TimeBeforeNextRound) {
        TimeBeforeNextRound->SetText(FText::FromString(FString::Printf(TEXT("%d"), Seconds)));
    }
}

void UPlayerUI::UpdateRound(int32 RoundNumber) {
    if (CurrentRound) {
        CurrentRound->SetText(FText::FromString(FString::Printf(TEXT("%d"), RoundNumber)));
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

void UPlayerUI::UpdateKnightNumber(int32 KnightNumber) {
    KnightNumberText->SetText(FText::FromString(FString::Printf(TEXT("%d"), KnightNumber)));
}

void UPlayerUI::UpdateArcherNumber(int32 ArcherNumber) {
    ArcherNumberText->SetText(FText::FromString(FString::Printf(TEXT("%d"), ArcherNumber)));
}