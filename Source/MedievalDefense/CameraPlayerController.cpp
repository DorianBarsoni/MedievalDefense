// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "Math/Vector2D.h"
#include "CameraPlayerPawn.h"

FVector2D MousePosition;

ACameraPlayerController::ACameraPlayerController() {
	minX = -350; maxX = 4400; minY = -180; maxY = 9413; speed = 50;
	APlayerController::bShowMouseCursor = 1;
}

void ACameraPlayerController::BeginPlay() {
}

void ACameraPlayerController::Tick(float DeltaSeconds) {
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	APlayerController::GetMousePosition(MousePosition.X, MousePosition.Y);

	ACameraPlayerPawn* ControlledPawn = Cast<ACameraPlayerPawn>(GetPawn());
	if (ControlledPawn) {
		FVector location = ControlledPawn->GetTargetLocation();

		if (MousePosition.X <= 20 && location.Y + speed < maxY) {
			location.Y += speed;
			ControlledPawn->SetActorLocation(location);
		}

		if (MousePosition.X >= ViewportSize.X - 20 && location.Y - speed > minY) {
			location.Y -= speed;
			ControlledPawn->SetActorLocation(location);
		}

		if (MousePosition.Y <= 20 && location.X - speed > minX) {
			location.X -= speed;
			ControlledPawn->SetActorLocation(location);
		}

		if (MousePosition.Y >= ViewportSize.Y - 20 && location.X + speed < maxX) {
			location.X += speed;
			ControlledPawn->SetActorLocation(location);
		}

		UE_LOG(LogTemp, Warning, TEXT("Mouse : %s"), *MousePosition.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Viewport : %s"), *ViewportSize.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Player : %s"), *location.ToString());
	}
}

