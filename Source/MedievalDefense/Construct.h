#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LifeComponent.h"
#include "Construct.generated.h"

UCLASS()
class MEDIEVALDEFENSE_API AConstruct : public AActor
{
	GENERATED_BODY()
	
public:	
	AConstruct();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULifeComponent* LifeComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
