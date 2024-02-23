// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBar.h"
#include "HealthBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALDEFENSE_API UHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UHealthBarWidgetComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> HealthWidgetTemplate;

	UPROPERTY()
	UHealthBar* HealthBarWidget;

	UFUNCTION(BlueprintCallable)
	void ChangeHealthPoints(int healthPoints, int maxHealth);
	
};
