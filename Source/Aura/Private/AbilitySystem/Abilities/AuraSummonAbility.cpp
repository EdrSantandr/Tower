// Copyright Eder


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location =  GetAvatarActorFromActorInfo()->GetActorLocation();

	const float DeltaSpread = SpawnSpread / NumMinions;
	TArray<FVector> SpawnLocations;
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	for(int32 i = 0; i<NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread*i, FVector::UpVector);
		const FVector ChosenSpawnLocation = Location + Direction* FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnLocations.Add(ChosenSpawnLocation);
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 15.f, 12, FColor::Green,false, 3.f);
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction * MaxSpawnDistance, 4.f, FLinearColor::Green, 4.f);
		DrawDebugSphere(GetWorld(), Location + Direction*MinSpawnDistance, 5.f, 12, FColor::Red,false, 3.f);
		DrawDebugSphere(GetWorld(), Location + Direction*MaxSpawnDistance, 5.f, 12, FColor::Red,false, 3.f);
	}
	return SpawnLocations;
}
