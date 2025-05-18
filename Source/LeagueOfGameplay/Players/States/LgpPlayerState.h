// Herzig Melvyn - League of Gameplay

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "LgpPlayerState.generated.h"

class ULgpAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class LEAGUEOFGAMEPLAY_API ALgpPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ALgpPlayerState(const FObjectInitializer& ObjectInitializer);

	//~IAbilitySystemInterface interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~Enf of IAbilitySystemInterface interface

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LeagueOfGameplay|Abilities")
	TObjectPtr<ULgpAbilitySystemComponent> AbilitySystemComponent;
};
