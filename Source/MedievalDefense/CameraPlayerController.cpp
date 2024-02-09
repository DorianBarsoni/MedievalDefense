// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "Math/Vector2D.h"
#include "CameraPlayerPawn.h"
#include "CameraPlayerPawn.h"

FVector2D MousePosition;

ACameraPlayerController::ACameraPlayerController() {
	APlayerController::bShowMouseCursor = 1;
}

ACameraPlayerPawn *camera;

void ACameraPlayerController::BeginPlay() {
	camera = Cast<ACameraPlayerPawn>(GetPawn());
}

void ACameraPlayerController::Tick(float DeltaSeconds) {
	camera->PreviousPosition = camera->GetActorLocation();

	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	APlayerController::GetMousePosition(MousePosition.X, MousePosition.Y);

	if (camera) {
		FVector location = camera->GetTargetLocation();

		if (MousePosition.X <= 20) {
			location.Y += camera->speed;
			camera->SetActorLocation(location);
		}

		if (MousePosition.X >= ViewportSize.X - 20) {
			location.Y -= camera->speed;
			camera->SetActorLocation(location);
		}

		if (MousePosition.Y <= 20) {
			location.X -= camera->speed;
			camera->SetActorLocation(location);
		}

		if (MousePosition.Y >= ViewportSize.Y - 20) {
			location.X += camera->speed;
			camera->SetActorLocation(location);
		}
	}
}

