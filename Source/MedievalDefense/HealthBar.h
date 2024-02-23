#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthBar.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API UHealthBar : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UProgressBar* HealthBar;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* HealthPointsText;

    UFUNCTION(BlueprintCallable, Category = "Health")
    void ChangeHealthPoints(int healthPoints, int maxHealth);
};
