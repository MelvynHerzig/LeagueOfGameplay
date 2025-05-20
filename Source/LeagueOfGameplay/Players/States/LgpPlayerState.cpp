// Herzig Melvyn - League of Gameplay


#include "Players/States/LgpPlayerState.h"

#include "Abilities/Attributes/LgpHealthAttributeSet.h"
#include "Abilities/Components/LgpAbilitySystemComponent.h"

ALgpPlayerState::ALgpPlayerState(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<ULgpAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	HealthAttributeSet = CreateDefaultSubobject<ULgpHealthAttributeSet>(TEXT("HealthAttributeSet"));
}

UAbilitySystemComponent* ALgpPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
