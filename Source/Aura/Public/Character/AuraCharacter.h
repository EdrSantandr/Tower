// Copyright Eder

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//Player Interface
	virtual void AddToXp_Implementation(int32 InXP) override;

	virtual void LevelUp_Implementation() override;
	//Combat interface
	virtual int32 GetPlayerLevel_Implementation() override;

protected:
	virtual void InitAbilityActorInfo() override;
};
