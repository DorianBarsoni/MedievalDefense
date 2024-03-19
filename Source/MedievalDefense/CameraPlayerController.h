#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerUI.h"
#include "Components/WidgetComponent.h"
#include "CameraPlayerController.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API ACameraPlayerController : public APlayerController
{
	GENERATED_BODY()

	FRotator Rotation;
	FVector ForwardVector;
	FVector RightVector;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* PlayerUIWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* MenuUIWidget;

	UPlayerUI* PlayerUI;

	UUserWidget* MenuUI;

	ACameraPlayerController();

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void DisplayMenu();
};
