#include "CameraPlayerController.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "Math/Vector2D.h"
#include "CameraPlayerPawn.h"
#include "PlayerInventorySubsystem.h"

FVector2D MousePosition;

ACameraPlayerController::ACameraPlayerController() {
	APlayerController::bShowMouseCursor = 1;

	PlayerUIWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerUI"));
	MenuUIWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MenuUI"));
}

ACameraPlayerPawn* camera;

void ACameraPlayerController::BeginPlay() {
	Super::BeginPlay();

	camera = Cast<ACameraPlayerPawn>(GetPawn());
	Rotation = camera->GetControlRotation();
	ForwardVector = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
	RightVector = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	PlayerUI = Cast<UPlayerUI>(PlayerUIWidget->GetWidget());
	if (PlayerUI) {
		PlayerUI->AddToViewport();
	}

	MenuUI = MenuUIWidget->GetWidget();
	if (MenuUI) {
		MenuUI->SetVisibility(ESlateVisibility::Hidden);
		MenuUI->AddToViewport();
	}

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer) {
		UPlayerInventorySubsystem* InventorySubsystem = LocalPlayer->GetSubsystem<UPlayerInventorySubsystem>();
		InventorySubsystem->NumberOfKnightInvocable = 0;
		InventorySubsystem->NumberOfArcherInvocable = 0;
		if (InventorySubsystem) {
			if (PlayerUI) {
				PlayerUI->UpdateKnightNumber(InventorySubsystem->NumberOfKnightInvocable);
				PlayerUI->UpdateArcherNumber(InventorySubsystem->NumberOfArcherInvocable);
			}
		}
	}
}

void ACameraPlayerController::Tick(float DeltaSeconds) {
	camera->PreviousPosition = camera->GetActorLocation();

	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	APlayerController::GetMousePosition(MousePosition.X, MousePosition.Y);

	if (camera) {
		FVector location = camera->GetTargetLocation();

		if (MousePosition.X <= 20) {
			location -= RightVector * camera->speed;
			camera->SetActorLocation(location);
		}

		if (MousePosition.X >= ViewportSize.X - 20) {	
			location += RightVector * camera->speed;
			camera->SetActorLocation(location);
		}

		if (MousePosition.Y <= 20) {
			location += ForwardVector * camera->speed;
			camera->SetActorLocation(location);
		}

		if (MousePosition.Y >= ViewportSize.Y - 20) {
			location -= ForwardVector * camera->speed;
			camera->SetActorLocation(location);
		}
	}
}

void ACameraPlayerController::DisplayMenu() {
	if (MenuUI->GetVisibility() == ESlateVisibility::Hidden) {
		MenuUI->SetVisibility(ESlateVisibility::Visible);
		PlayerUI->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		MenuUI->SetVisibility(ESlateVisibility::Hidden);
		PlayerUI->SetVisibility(ESlateVisibility::Visible);
	}
}

