#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LifeComponent.h"
#include "TroopDataAsset.h"
#include "TeamComponent.h"
#include "HealthBarWidgetComponent.h"
#include "TroopCharacter.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API ATroopCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULifeComponent *LifeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTeamComponent *TeamComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTroopDataAsset *TroopDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHealthBarWidgetComponent* HealthBarWidgetComponent;
	
	ATroopCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MakeTroopAlly();

	UFUNCTION(BlueprintCallable)
	void MakeTroopEnemy();

	UFUNCTION(BlueprintCallable)
	void GetDamage(int damagePoints);

};
