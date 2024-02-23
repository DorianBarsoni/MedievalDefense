#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PlayerUI.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* KnightButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* KnightText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ArcherButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ArcherText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TroopCharacter")
	TSubclassOf<AActor> KnightActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TroopCharacter")
	TSubclassOf<AActor> ArcherActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius;

private:
	UFUNCTION(BlueprintCallable)
	void onKnightButtonClicked(FVector SpawnPoint);

	UFUNCTION(BlueprintCallable)
	void onArcherButtonClicked(FVector SpawnPoint);

	FVector getSpawnPoint(FVector SpawnPoint);
	
};
