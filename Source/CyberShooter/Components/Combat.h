#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat.generated.h"

class ACharacter_Base;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERSHOOTER_API UCombat : public UActorComponent
{
	GENERATED_BODY()

public:	
	// CONSTRUCTOR
	UCombat();

	// FUNCTIONS
	void Attack();

	float GetAttackRange() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// VARIABLES
	UPROPERTY()
	ACharacter_Base *Character;

	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem *ImpactEffect;

	UPROPERTY(EditAnywhere)
	USoundBase *MuzzleSound;

	UPROPERTY(EditAnywhere)
	float AttackRange = 200.f;

	UPROPERTY()
	float Damage = 20.f;

	//FUNCTIONS
	void AttackMelee();

	void AttackRanged();

	bool AttackTrace(FHitResult &Hit, FVector &AttackDirection);

	AController *GetOwnerController() const;	
};
