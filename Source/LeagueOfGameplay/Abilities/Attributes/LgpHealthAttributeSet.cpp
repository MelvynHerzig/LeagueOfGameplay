// Herzig Melvyn - League of Gameplay


#include "Abilities/Attributes/LgpHealthAttributeSet.h"

#include "Net/UnrealNetwork.h"

ULgpHealthAttributeSet::ULgpHealthAttributeSet()
{
	InitMaxHealth(600.0f);
	InitHealth(GetMaxHealth());
}

void ULgpHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ULgpHealthAttributeSet, Health);
	DOREPLIFETIME(ULgpHealthAttributeSet, MaxHealth);
}
