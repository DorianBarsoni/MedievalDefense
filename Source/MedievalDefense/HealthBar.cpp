#include "HealthBar.h"

void UHealthBar::ChangeHealthPoints(int healthPoints, int maxHealth) {
    if (HealthPointsText) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Widget : %d %d"), healthPoints, maxHealth));

        FString FormattedString = FString::Printf(TEXT("%d / %d"), healthPoints, maxHealth);
        if (HealthPointsText) {
            HealthPointsText->SetText(FText::FromString(FormattedString));
        } else GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("CA MARCHE PAS")));
        

        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FormattedString);

        float healthPercentage = static_cast<float>(healthPoints) / static_cast<float>(maxHealth);
        if (HealthBar != nullptr) {
            HealthBar->SetPercent(healthPercentage);
        }
    }
}
