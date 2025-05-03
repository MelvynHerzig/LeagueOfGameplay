// Herzig Melvyn - League of Gameplay

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LGPCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * ALyraCharacter
 *
 *	The base character pawn class used by League of Gameplay..
 */
UCLASS(Config = Game, Meta = (ShortTooltip = "The base character class used by League of Gameplay."))
class LEAGUEOFGAMEPLAY_API ALGPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALGPCharacter(const FObjectInitializer& ObjectInitializer);

	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* CameraComponent;
};
