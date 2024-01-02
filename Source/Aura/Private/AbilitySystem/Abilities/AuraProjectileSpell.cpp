// Copyright Eder


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

FString UAuraProjectileSpell::GetDescription(int32 Level)
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

FString UAuraProjectileSpell::GetNextLevelDescription(int32 Level)
{
	FGameplayTag FireDamageType = FAuraGameplayTags::Get().Damage_Fire;
	const int32 Damage = DamageTypes[FireDamageType].GetValueAtLevel(Level+1);
	return FString::Printf(TEXT("<Title>NEXT LEVEL</>\n<Default>Launches </><Level>%d</><Default> bolts of fire, exploding on impact and dealing: </>\n<Damage>%d</><Default> fire damage with a chance to burn.</>\n\n<Small>Level: </><Level>%d</>"),FMath::Min(Level, NumProjectiles), Damage, Level);
}

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	//Fix because we change de definition of the function
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	//Rotation.Pitch = 0.f;

	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	// Just for testing
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);
	TArray<TWeakObjectPtr<AActor>> Actors;
	Actors.Add(Projectile);
	EffectContextHandle.AddActors(Actors);
	FHitResult HitResult;
	HitResult.Location = ProjectileTargetLocation;
	EffectContextHandle.AddHitResult(HitResult);
		
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);
	//Setup by caller the damage using gameplaytag
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	//Now we should get the damage from the tmap
	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,Pair.Key,ScaledDamage);
	}
		
	Projectile->DamageEffectSpecHandle = SpecHandle;
		
	Projectile->FinishSpawning(SpawnTransform);
}
