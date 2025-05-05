// Herzig Melvyn - League of Gameplay

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LgpGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFGAMEPLAY_API ALgpGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ALgpGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
