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


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius;

private:
	UFUNCTION(BlueprintCallable)
	bool onKnightButtonClicked(FVector SpawnPoint);

	UFUNCTION(BlueprintCallable)
	bool onArcherButtonClicked(FVector SpawnPoint);

	bool SpawnSpecificActor(FVector SpawnPoint, UClass* ActorClassToSpawn);

	FVector getSpawnPoint(FVector SpawnPoint);
	
};
