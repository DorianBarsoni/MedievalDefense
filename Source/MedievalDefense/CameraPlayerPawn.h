#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraLimitationArea.h"
#include "TroopCharacter.h"
#include "CameraPlayerPawn.generated.h"

UCLASS(Blueprintable)
class MEDIEVALDEFENSE_API ACameraPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACameraLimitationArea *CameraLimitationArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;

	UPROPERTY()
	FVector PreviousPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATroopCharacter*> SelectedTroops;

	TPair<FVector, FVector> HoldAndReleaseCoordinates;

	bool isFirstHold;

	ACameraPlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void LeftMousePressed();

	UFUNCTION(BlueprintCallable)
	void RightClickPressed();

	UFUNCTION(BlueprintCallable)
	void LeftClickHold();

	UFUNCTION(BlueprintCallable)
	FVector LeftClickHoldAndReleased();

private:
	bool TraceLineFromCameraToMousePosition(FHitResult &HitResult);

	void SelectTroops(TArray<ATroopCharacter*> NewSelectedTroops);

	void UnselectTroops();

};
