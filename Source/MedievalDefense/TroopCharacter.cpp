// Fill out your copyright notice in the Description page of Project Settings.


#include "TroopCharacter.h"

// Sets default values
ATroopCharacter::ATroopCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));
}

// Called when the game starts or when spawned
void ATroopCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATroopCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATroopCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

