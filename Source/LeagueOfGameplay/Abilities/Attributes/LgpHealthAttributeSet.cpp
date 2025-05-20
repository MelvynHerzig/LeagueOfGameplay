// Herzig Melvyn - League of Gameplay


#include "Abilities/Attributes/LgpHealthAttributeSet.h"

#include "Net/UnrealNetwork.h"

ULgpHealthAttributeSet::ULgpHealthAttributeSet()
{
	InitHealth(600.0f);
	InitMaxHealth(600.0f);
}

void ULgpHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ULgpHealthAttributeSet, Health);
	DOREPLIFETIME(ULgpHealthAttributeSet, MaxHealth);
}
