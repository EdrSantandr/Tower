// Copyright Eder


#include "AbilitySystem/Abilities/AuraFirebolt.h"

#include "AuraGameplayTags.h"

FString UAuraFirebolt::GetDescription(int32 Level)
{
	FGameplayTag FireDamageType = FAuraGameplayTags::Get().Damage_Fire;
	const int32 Damage = DamageTypes[FireDamageType].GetValueAtLevel(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT("<Title>FIRE BOLT</>\n<Default>Launches a bolt of fire, exploding on impact and dealing: </>\n<Damage>%d</><Default> fire damage with a chance to burn.</>\n\n<Small>Level: </><Level>%d</>"), Damage, Level);		
	}
	else
	{
		return FString::Printf(TEXT("<Title>FIRE BOLT</>\n<Default>Launches </><Level>%d</><Default> bolts of fire, exploding on impact and dealing: </>\n<Damage>%d</><Default> fire damage with a chance to burn.</>\n\n<Small>Level: </><Level>%d</>"),FMath::Min(Level, NumProjectiles), Damage, Level);		
	}
}

FString UAuraFirebolt::GetNextLevelDescription(int32 Level)
{
	FGameplayTag FireDamageType = FAuraGameplayTags::Get().Damage_Fire;
	const int32 Damage = DamageTypes[FireDamageType].GetValueAtLevel(Level+1);
	return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n<Default>Launches </><Level>%d</><Default> bolts of fire, exploding on impact and dealing: </>\n<Damage>%d</><Default> fire damage with a chance to burn.</>\n\n<Small>Level: </><Level>%d</>"),FMath::Min(Level, NumProjectiles), Damage, Level);
}