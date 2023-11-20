// Copyright Eder

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType >
	void BindAbilityInputActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc );
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraEnhancedInputComponent::BindAbilityInputActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FAuraInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressedFunc,Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}
			
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
			
		}
	}
}
