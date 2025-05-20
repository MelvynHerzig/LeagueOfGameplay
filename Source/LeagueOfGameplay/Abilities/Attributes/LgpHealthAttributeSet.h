// Herzig Melvyn - League of Gameplay

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "LgpHealthAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Attribute set for health-related attributes.
 */
UCLASS()
class LEAGUEOFGAMEPLAY_API ULgpHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	ULgpHealthAttributeSet();
	
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	ATTRIBUTE_ACCESSORS(ULgpHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(ULgpHealthAttributeSet, MaxHealth);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "LeagueOfGameplay|Attributes|Health")
	FGameplayAttributeData Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "LeagueOfGameplay|Attributes|Health")
	FGameplayAttributeData MaxHealth;
};
