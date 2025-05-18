// Herzig Melvyn - League of Gameplay


#include "Players/States/LgpPlayerState.h"

#include "Abilities/Components/LgpAbilitySystemComponent.h"

ALgpPlayerState::ALgpPlayerState(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<ULgpAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

UAbilitySystemComponent* ALgpPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
