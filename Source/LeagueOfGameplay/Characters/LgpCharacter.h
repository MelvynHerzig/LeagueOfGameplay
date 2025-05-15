// Herzig Melvyn - League of Gameplay

#pragma once

#include "CoreMinimal.h"
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
class LEAGUEOFGAMEPLAY_API ALgpCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALgpCharacter(const FObjectInitializer& ObjectInitializer);

	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface
};
