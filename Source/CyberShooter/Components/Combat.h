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
	USoundBase *ImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackRange = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackDelay = 0.9f;

	FTimerHandle AttackTimer;

	//FUNCTIONS
	void AttackMelee();

	void AttackRanged();

	void AttackReset();

	bool AttackTrace(FHitResult &Hit, FVector &AttackDirection);

	AController *GetOwnerController() const;	
};
