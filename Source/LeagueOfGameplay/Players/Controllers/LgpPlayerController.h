// Herzig Melvyn - League of Gameplay

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LgpPlayerController.generated.h"

class ALgpCamera;
class UNiagaraSystem;
class UInputAction;
class UInputMappingContext;
/**
 * The base player controller class used by League of Gameplay.
 */
UCLASS(Meta = (ShortTooltip = "The base player controller class used by League of Gameplay."))
class LEAGUEOFGAMEPLAY_API ALgpPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALgpPlayerController();

	FORCEINLINE ALgpCamera* GetPlayerCamera() const { return PlayerCamera; }

protected:
	/** Called when the player presses the MoveTo action. Get destination and spawn cursor fx. */
	void OnMoveToStarted();
	/** Called when the player keeps the pressure on the MoveToAction. Update destination, add movement input to destination */
	void OnMoveToTriggered();
	/** Called when the player releases the MoveTo action or if the input is canceled. Move to the destination */
	void OnMoveToReleased();
	
	//~APlayerController interface
	void SetupInputComponent() override;
	void OnPossess(APawn* InPawn) override;
	//~End of APlayerController interface

private:
	/**
	 * Query for hit result under mouse cursor.
	 * @param Location The Location behind the cursor.
	 * return true if the hit result is valid, false otherwise.
	 */
	bool QueryHitLocationUnderCursor(FVector& Location);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LeagueOfGameplay|Camera")
	TSubclassOf<ALgpCamera> CameraClass;
	
private:
	UPROPERTY()
	TObjectPtr<ALgpCamera> PlayerCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LeagueOfGameplay|Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LeagueOfGameplay|Input|MoveTo", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveToAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LeagueOfGameplay|Input|MoveTo", meta=(AllowPrivateAccess = "true"))
	UNiagaraSystem* FXCursor;

	/** Coordinate of the destination where the player wants to move. */
	FVector Destination;
};
