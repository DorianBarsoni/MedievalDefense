#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "PlayerUI.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* KnightButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* KnightText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* KnightNumberText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ArcherButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ArcherText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TroopCharacter")
	TSubclassOf<AActor> KnightActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TroopCharacter")
	TSubclassOf<AActor> ArcherActor;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ArcherNumberText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimeBeforeNextRound;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentRound;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* DefeatCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius;

	UFUNCTION(BlueprintCallable)
	void UpdateTimeBeforeNextRound(int32 Seconds);

	UFUNCTION(BlueprintCallable)
	void UpdateRound(int32 RoundNumber);

	UFUNCTION(BlueprintCallable)
	void UpdateKnightNumber(int32 KnightNumber);

	UFUNCTION(BlueprintCallable)
	void UpdateArcherNumber(int32 ArcherNumber);

private:
	UFUNCTION(BlueprintCallable)
	bool onKnightButtonClicked(FVector SpawnPoint);

	UFUNCTION(BlueprintCallable)
	bool onArcherButtonClicked(FVector SpawnPoint);

	bool SpawnSpecificActor(FVector SpawnPoint, UClass* ActorClassToSpawn);

	FVector getSpawnPoint(FVector SpawnPoint);
	
};
