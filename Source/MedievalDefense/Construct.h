#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LifeComponent.h"
#include "GameplayTagContainer.h"
#include "Components/WidgetComponent.h"
#include "HealthBar.h"
#include "ConstructDataAsset.h"
#include "Construct.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API AConstruct : public AActor
{
	GENERATED_BODY()
	
public:	
	AConstruct();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag TeamTag;

	UPROPERTY(EditAnywhere)
	UConstructDataAsset* ConstructDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULifeComponent* LifeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* HealthComponentWidget;

	UHealthBar* WidgetAsHealthBar;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GetDamage(int damagePoints);

};
