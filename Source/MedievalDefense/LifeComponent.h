#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthBar.h"
#include "LifeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALDEFENSE_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULifeComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLife;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Components")
	void GetDamage(int damagePoints);
};
