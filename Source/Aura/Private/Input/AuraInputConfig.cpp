// Copyright Eder


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for(const FAuraInputAction Action:AbilityInputActions)
	{
		if(Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant find Abitilityinputaction for input tag [%s] on input config [%s]"), *InputTag.ToString(), *GetNameSafe(this));
		
	}
	return nullptr;
}
