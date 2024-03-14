#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "PlayerInventorySubsystem.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API UPlayerInventorySubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfKnightInvocable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfArcherInvocable;

	UPlayerInventorySubsystem();
};
