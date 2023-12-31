// Copyright Eder

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraBeamSpell.generated.h"

/**
 * 
 */
struct FSortByDistance
{
	explicit FSortByDistance(const FVector& InSourceLocation)
		: SourceLocation(InSourceLocation)
	{
	}

	/* The Location to use in our Sort comparison. */
	FVector SourceLocation = FVector::Zero();

	bool operator()(const AActor* A, const AActor* B) const
	{
		float DistanceA = FVector::DistSquared(SourceLocation, A->GetActorLocation());
		float DistanceB = FVector::DistSquared(SourceLocation, B->GetActorLocation());

		return DistanceA < DistanceB;
	}
};

UCLASS()
class AURA_API UAuraBeamSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void StoreMouseDataInfo(const FHitResult& HitResult );

	UFUNCTION(BlueprintCallable)
	void StoreOwnerVariables();

	UFUNCTION(BlueprintCallable)
	void TraceFirstTarget(const FVector& BeamTargetLocation);

	UFUNCTION(BlueprintCallable)
	void StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets);

	UPROPERTY(EditDefaultsOnly, Category="Beam")
	float BeamMaxRadiusRange = 850.f;
	
protected:

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	FVector MouseHitLocation;

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	TObjectPtr<AActor> MouseHitActor;

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	TObjectPtr<APlayerController> OwnerPlayerController;

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	TObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY(EditDefaultsOnly, Category="Beam")
	int32 MaxNumShockTargets = 5;
};
