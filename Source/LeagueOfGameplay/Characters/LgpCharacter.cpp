// Herzig Melvyn - League of Gameplay

#include "Characters/LgpCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
