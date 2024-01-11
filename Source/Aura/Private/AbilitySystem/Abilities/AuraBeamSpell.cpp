// Copyright Eder


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Aura/AuraLogChannels.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if(HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if(CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter);
	if (OwnerCharacter->Implements<UCombatInterface>())
	{
		if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(OwnerCharacter);
			FHitResult HitResult;
			const FVector SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
			
			UKismetSystemLibrary::SphereTraceSingle(OwnerCharacter, SocketLocation, BeamTargetLocation, 10.f,
				TraceTypeQuery1, false,
				ActorsToIgnore, EDrawDebugTrace::None,HitResult, true );

			if(HitResult.bBlockingHit)
			{
				MouseHitLocation = HitResult.ImpactPoint;
				MouseHitActor = HitResult.GetActor();
			}
		}
	}
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor* > ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorsToIgnore.Add(MouseHitActor);
	TArray<AActor* > OverlappingActors;
	FVector OriginLocation = MouseHitActor->GetActorLocation();
	int32 NumAdditionalTargets = 5;
	
	UAuraAbilitySystemLibrary::GetLifePlayersWithinRadius(GetAvatarActorFromActorInfo(),
		OverlappingActors,
		ActorsToIgnore,
		BeamMaxRadiusRange,
		MouseHitActor->GetActorLocation());
	
	if (OverlappingActors.Num()<= NumAdditionalTargets)
	{
		OutAdditionalTargets = OverlappingActors;
	}
	else
	{
		int32 Index = 0;
		Algo::Sort(OverlappingActors, FSortByDistance(OriginLocation));
		while(Index< NumAdditionalTargets)
		{
			OutAdditionalTargets.Add(OverlappingActors[Index]);
			Index++;
		}
	}
	
	/*
	TArray<AActor* > OverlappingActorsToSort = OverlappingActors;
	FVector OriginLocation = MouseHitActor->GetActorLocation();
	int32 NumAdditionalTargets = 5;
	UAuraAbilitySystemLibrary::GetClosestTargets(NumAdditionalTargets, OverlappingActors, OutAdditionalTargets, MouseHitActor->GetActorLocation());
	*/
	//sORT the array
	
	/* Just to Test values
	for (AActor* ActorSorted : OutAdditionalTargets)
	{
		float Distance = (ActorSorted->GetActorLocation() - OriginLocation).Length();
		UE_LOG(LogAura, Warning, TEXT("NAME: [%s] distance [%f]"), *ActorSorted->GetName(), Distance);
	}
	*/
}
