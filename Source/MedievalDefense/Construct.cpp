// Fill out your copyright notice in the Description page of Project Settings.


#include "Construct.h"

// Sets default values
AConstruct::AConstruct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));

}

// Called when the game starts or when spawned
void AConstruct::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConstruct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

