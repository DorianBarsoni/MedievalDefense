#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "TroopDataAsset.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API UTroopDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag TeamTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpeedMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int LifePoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxLifePoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown;
	
};
