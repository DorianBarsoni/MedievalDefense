#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALDEFENSE_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int life;

public:	
	ULifeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Components")
	void GetDamage(int damagePoint);

	UFUNCTION(BlueprintCallable, Category = "Components")
	void SetLife(int lifePoint);

	UFUNCTION(BlueprintCallable, Category = "Components")
	int GetLife();
	
	/*UFUNCTION(BlueprintCallable, Category = "Components")
	virtual void Die() PURE_VIRTUAL(ULifeComponent::Die,);*/
};
