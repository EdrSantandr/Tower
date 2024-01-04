// Copyright Eder

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AuraExecCalcDamage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraExecCalcDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UAuraExecCalcDamage();
	void DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                     const FGameplayEffectSpec& Spec,
	                     FAggregatorEvaluateParameters EvaluateParameters,
	                     const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const;

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
