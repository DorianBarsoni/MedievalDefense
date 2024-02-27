#include "HealthBar.h"

void UHealthBar::ChangeHealthPoints(int healthPoints, int maxHealth) {
    if (HealthPointsText) {
        
        FString FormattedString = FString::Printf(TEXT("%d / %d"), healthPoints, maxHealth);
        if (HealthPointsText) {
            HealthPointsText->SetText(FText::FromString(FormattedString));
        }

        float healthPercentage = static_cast<float>(healthPoints) / static_cast<float>(maxHealth);
        if (HealthBar) {
            if (healthPercentage <= 0.2) {
                HealthBar->SetFillColorAndOpacity(FLinearColor::Red);
            } else if (healthPercentage <= 0.4) {
                HealthBar->SetFillColorAndOpacity(FLinearColor::Yellow);
            }

            HealthBar->SetPercent(healthPercentage);
        }
    }
}
