#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraLimitationArea.generated.h"

UCLASS()
class MEDIEVALDEFENSE_API ACameraLimitationArea : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* LocationVolume;

	ACameraLimitationArea();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
