#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ConstructDataAsset.generated.h"

UCLASS()
class MEDIEVALDEFENSE_API UConstructDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int LifePoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxLifePoints;
	
};
