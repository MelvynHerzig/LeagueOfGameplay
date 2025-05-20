// Herzig Melvyn - League of Gameplay

#include "Characters/LgpCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Core/Logging/LgpLogging.h"
#include "Players/States/LgpPlayerState.h"

ALgpCharacter::ALgpCharacter(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	// Don't rotate character to camera direction, because to we want to use movement direction.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Set up movement
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Set up  capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
}

void ALgpCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALgpCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Client is set up inside OnRep_PlayerState
	if (ALgpPlayerState* LgpPlayerState = GetPlayerState<ALgpPlayerState>())
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = LgpPlayerState->GetAbilitySystemComponent())	
		{
			AbilitySystemComponent->InitAbilityActorInfo(LgpPlayerState, this);
		}
		else
		{
			UE_LOG(LogLgp, Warning, TEXT("[LgpCharacter] LgpPlayerState does not have a valid AbilitySystemComponent."));
		}
	}
}

void ALgpCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (GetWorld()->IsNetMode(NM_Client))
	{
		if (ALgpPlayerState* LgpPlayerState = GetPlayerState<ALgpPlayerState>())
		{
			if (UAbilitySystemComponent* LgpAbilitySystemComponent = LgpPlayerState->GetAbilitySystemComponent())
			{
				LgpAbilitySystemComponent->InitAbilityActorInfo(LgpPlayerState, this);
			}
			else
			{
				UE_LOG(LogLgp, Warning, TEXT("[LgpCharacter] LgpPlayerState does not have a valid AbilitySystemComponent."));
			}
		}
	}
}

UAbilitySystemComponent* ALgpCharacter::GetAbilitySystemComponent() const
{
	return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPlayerState());
}
