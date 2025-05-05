// Herzig Melvyn - League of Gameplay


#include "LgpPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "LeagueOfGameplay/LeagueOfGameplay.h"

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
	}
	else
	{
		UE_LOG(LogLgp, Warning, TEXT("InputComponent is not of type UEnhancedInputComponent. Please check your input settings."));
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
