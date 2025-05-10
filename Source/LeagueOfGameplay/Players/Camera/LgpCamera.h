// Herzig Melvyn - League of Gameplay

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LgpCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * This class is representing the camera actor that the player will be able to control to see the map.
 * This is not directly linked to the LgpCharacter, because the camera is independent of the character.
 */
UCLASS()
class LEAGUEOFGAMEPLAY_API ALgpCamera : public AActor
{
	GENERATED_BODY()

public:
	ALgpCamera();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
};
