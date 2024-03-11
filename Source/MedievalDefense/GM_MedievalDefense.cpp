// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MedievalDefense.h"
#include "TimerManager.h"


AGM_MedievalDefense::AGM_MedievalDefense()
{
	RoundNumber = 0;
	PreparationTime = 60;
}


void AGM_MedievalDefense::BeginPlay() {
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGM_MedievalDefense::TimerFunction, 1.0f, true, 1.0f);
}

void AGM_MedievalDefense::TimerFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Temps écoulé : %d secondes"), RoundNumber));

	UpdateTimer.Broadcast(PreparationTime);

	if (PreparationTime <= 0) {
		PreparationTime = 60;
		RoundNumber++;
		GetWorldTimerManager().ClearTimer(TimerHandle);
		UpdateRound.Broadcast(RoundNumber);
	}
	PreparationTime--;
}

void AGM_MedievalDefense::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(TimerHandle);

	Super::EndPlay(EndPlayReason);
}

