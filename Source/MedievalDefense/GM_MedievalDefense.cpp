// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MedievalDefense.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "CameraPlayerController.h"
#include "PlayerInventorySubsystem.h"
#include "Components/AudioComponent.h"
#include "AttackNotify.h"


AGM_MedievalDefense::AGM_MedievalDefense()
{
	RoundNumber = 0;
	PreparationTime = 60;
}


void AGM_MedievalDefense::BeginPlay() {
	Super::BeginPlay();

	if (SpawningSystemType) {
		SpawningSystem = GetWorld()->SpawnActor<AAISpawningSystem>(SpawningSystemType);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandleStartup, this, &AGM_MedievalDefense::OnStartupDelayFinished, 1.0f, false);
}

void AGM_MedievalDefense::OnStartupDelayFinished() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors) {
		AEnemySpawner* EnemySpawner = Cast<AEnemySpawner>(Actor);
		if (EnemySpawner) {
			SpawningSystem->EnemySpawners.Add(EnemySpawner);
		}
	}
	SpawningSystem->InitSpawningSystem();

	NextRound();
}

void AGM_MedievalDefense::TimerFunction()
{
	UpdateTimer.Broadcast(CurrentTime);

	if (CurrentTime <= 0) {
		GetWorldTimerManager().ClearTimer(TimerHandle);
		UpdateRound.Broadcast(RoundNumber);
		SpawnEnemies();
		if (PreparationMusicAudioComponent != nullptr) PreparationMusicAudioComponent->Stop();
		DrumsAudioComponent = UGameplayStatics::SpawnSound2D(this, Drums);
		DrumsAudioComponent->OnAudioFinished.AddDynamic(this, &AGM_MedievalDefense::OnDrumsMusicFinished);
	}
	CurrentTime--;
}

void AGM_MedievalDefense::SpawnEnemies() {
	NumberOfEnemiesCurrentlyAlive = SpawningSystem->SpawnEnemies(CurrentAmoutOfEnemies);
}

void AGM_MedievalDefense::EnemyKilled() {
	if (--NumberOfEnemiesCurrentlyAlive <= 0) {
		NextRound();
	}
}

void AGM_MedievalDefense::NextRound() {
	if (AssaultMusicAudioComponent) AssaultMusicAudioComponent->Stop();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraPlayerController::StaticClass(), FoundActors);
	for (AActor* Actor : FoundActors) {
		if (ACameraPlayerController* CameraPlayerController = Cast<ACameraPlayerController>(Actor)) {
			ULocalPlayer* LocalPlayer = CameraPlayerController->GetLocalPlayer();
			if (LocalPlayer) {
				UPlayerInventorySubsystem* InventorySubsystem = LocalPlayer->GetSubsystem<UPlayerInventorySubsystem>();
				if (InventorySubsystem) {
					InventorySubsystem->NumberOfKnightInvocable += NumberOfKnightToAdd;
					InventorySubsystem->NumberOfArcherInvocable += NumberOfArcherToAdd;
					if (CameraPlayerController->PlayerUI) {
						CameraPlayerController->PlayerUI->UpdateKnightNumber(InventorySubsystem->NumberOfKnightInvocable);
						CameraPlayerController->PlayerUI->UpdateArcherNumber(InventorySubsystem->NumberOfArcherInvocable);
					}
				}
			}
		}
	}

	CurrentTime = PreparationTime;
	CurrentAmoutOfEnemies += NumberOfEnemiesToAdd;
	//NumberOfEnemiesCurrentlyAlive = CurrentAmoutOfEnemies;
	RoundNumber++;
	if (RoundNumber != 1) {
		SpawningSystem->CalculateNewSpawningRate();
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGM_MedievalDefense::TimerFunction, 1.0f, true, 1.0f);
	PreparationMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, PreparationMusic);
}

void AGM_MedievalDefense::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(TimerHandle);

	Super::EndPlay(EndPlayReason);
}

void AGM_MedievalDefense::OnDrumsMusicFinished() {
	DrumsAudioComponent->Stop();
	AssaultMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, AssaultMusic);
}

void AGM_MedievalDefense::Defeat() {
	GetWorldTimerManager().ClearTimer(TimerHandle);

	AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraPlayerController::StaticClass());
	if (FoundActor) {
		if (ACameraPlayerController* CameraController = Cast<ACameraPlayerController>(FoundActor)) {
			CameraController->PlayerUI->DisplayDefeatUI();
		}
	}
}

