// Copyright Eder


#include "AbilitySystem/Abilities/AuraFirebolt.h"

#include "AuraGameplayTags.h"

FString UAuraFirebolt::GetDescription(int32 Level)
{
	FGameplayTag FireDamageType = FAuraGameplayTags::Get().Damage_Fire;
	const int32 Damage = GetDamageByDamageType(Level,FireDamageType);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing: </><Damage>%d</>"
			"<Default> fire damage with a chance to burn.</>"), Level,ManaCost,Cooldown, Damage);
	}
	else
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Launches </><Level>%d</><Default> a bolt of fire, "
			"exploding on impact and dealing: </><Damage>%d</>"
			"<Default> fire damage with a chance to burn.</>"), Level,ManaCost,Cooldown, FMath::Min(Level, NumProjectiles),Damage);
	}
}

FString UAuraFirebolt::GetNextLevelDescription(int32 Level)
{
	FGameplayTag FireDamageType = FAuraGameplayTags::Get().Damage_Fire;
	const int32 Damage = GetDamageByDamageType(Level,FireDamageType);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
			"<Title>NEXT LEVEL</>\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Launches </><Level>%d</><Default> a bolt of fire, "
			"exploding on impact and dealing: </><Damage>%d</>"
			"<Default> fire damage with a chance to burn.</>"), Level,ManaCost, Cooldown, FMath::Min(Level, NumProjectiles),Damage);
}