#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TroopController.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API ATroopController : public AAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void MoveTroopToLocation(FVector location);
};
