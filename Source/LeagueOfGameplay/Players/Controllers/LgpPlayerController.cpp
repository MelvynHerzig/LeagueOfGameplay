// Herzig Melvyn - League of Gameplay


#include "LgpPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "LeagueOfGameplay/LeagueOfGameplay.h"
#include "LeagueOfGameplay/Players/Camera/LgpCamera.h"

ALgpPlayerController::ALgpPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	Destination = FVector::ZeroVector;
}

void ALgpPlayerController::OnMoveToStarted()
{
	StopMovement();
	
	if (QueryHitLocationUnderCursor(Destination))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, Destination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

void ALgpPlayerController::OnMoveToTriggered()
{
	if (APawn* ControlledPawn = GetPawn())
	{
		QueryHitLocationUnderCursor(Destination);
		const FVector MovementDirection = (Destination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(MovementDirection, 1.0, false);
	}
}

void ALgpPlayerController::OnMoveToReleased()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
}

void ALgpPlayerController::OnZoomTriggered(const FInputActionValue& Value)
{
	PlayerCamera->Zoom(Value.Get<float>());
}

void ALgpPlayerController::OnLockCameraStarted()
{
	if (PlayerCamera)
	{
		PlayerCamera->Follow(GetPawn());
	}
}

void ALgpPlayerController::OnLockCameraReleased()
{
	if (PlayerCamera)
	{
		PlayerCamera->StopFollow();
	}
}

void ALgpPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Add the default mapping context
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Bind actions
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Move To Action
		EnhancedInputComponent->BindAction(MoveToAction, ETriggerEvent::Started, this, &ALgpPlayerController::OnMoveToStarted);
		EnhancedInputComponent->BindAction(MoveToAction, ETriggerEvent::Triggered, this, &ALgpPlayerController::OnMoveToTriggered);
		EnhancedInputComponent->BindAction(MoveToAction, ETriggerEvent::Completed, this, &ALgpPlayerController::OnMoveToReleased);
		EnhancedInputComponent->BindAction(MoveToAction, ETriggerEvent::Canceled, this, &ALgpPlayerController::OnMoveToReleased);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ALgpPlayerController::OnZoomTriggered);
		EnhancedInputComponent->BindAction(LockCameraAction, ETriggerEvent::Started, this, &ALgpPlayerController::OnLockCameraStarted);
		EnhancedInputComponent->BindAction(LockCameraAction, ETriggerEvent::Completed, this, &ALgpPlayerController::OnLockCameraReleased);
	}
	else
	{
		UE_LOG(LogLgp, Warning, TEXT("InputComponent is not of type UEnhancedInputComponent. Please check your input settings."));
	}
}

void ALgpPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Add a new camera and uses it.
	FVector CameraLocation = InPawn->GetActorLocation();
	if (PlayerCamera == nullptr)
	{
		PlayerCamera = GetWorld()->SpawnActor<ALgpCamera>(CameraClass, CameraLocation, FRotator::ZeroRotator);
		SetViewTarget(PlayerCamera);
	}
}

bool ALgpPlayerController::QueryHitLocationUnderCursor(FVector& Location)
{
	FHitResult HitResult;

	bool bHitSuccessful = GetHitResultUnderCursor(ECC_Visibility, true, HitResult);
	if (bHitSuccessful)
	{
		Location = HitResult.Location;
	}

	return bHitSuccessful;
}
