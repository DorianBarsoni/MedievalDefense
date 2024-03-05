#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CastleAttackableArea.generated.h"

UCLASS()
class MEDIEVALDEFENSE_API ACastleAttackableArea : public AActor
{
	GENERATED_BODY()
	
public:	
	ACastleAttackableArea();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* LocationVolume;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
