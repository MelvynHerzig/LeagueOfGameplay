// Herzig Melvyn - League of Gameplay

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "LgpCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * ALyraCharacter
 *
 *	The base character pawn class used by League of Gameplay.
 */
UCLASS(Config = Game, Meta = (ShortTooltip = "The base character class used by League of Gameplay."))
class LEAGUEOFGAMEPLAY_API ALgpCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ALgpCharacter(const FObjectInitializer& ObjectInitializer);

	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

	//~ACharacter interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	//~End of ACharacter interface

	//~IAbilitySystemInterface interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End of IAbilitySystemInterface interface
};
