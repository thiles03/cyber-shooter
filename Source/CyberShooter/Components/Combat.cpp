#include "Combat.h"
#include "CyberShooter/Characters/Character_Base.h"
#include "Kismet/GameplayStatics.h"

// Constructor
UCombat::UCombat()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCombat::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacter_Base>(GetOwner());
}

float UCombat::GetAttackRange() const
{
	return AttackRange;
}

void UCombat::Attack() 
{
	

	if (Character->CombatType == ECombatType::RANGED)
	{
		// Spawn muzzle sound and VFX
		if (MuzzleFlash && MuzzleSound)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Character->GetMesh(), TEXT("MuzzleSocket_Primary"));
			UGameplayStatics::SpawnSoundAttached(MuzzleSound, Character->GetMesh(), TEXT("MuzzleSocket_Primary"));
		}

		// Calculate hit location and direction
		FHitResult Hit;
		FVector AttackDirection;
		bool bSuccess = AttackTrace(OUT Hit, OUT AttackDirection);

		// If Character hit
		if (bSuccess)
		{			
			// Spawn impact VFX at hit location
			if (ImpactEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, (-AttackDirection).Rotation());
			}

			// Do damage to hit actor
			AActor *HitActor = Hit.GetActor();
			if (HitActor)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, AttackDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), GetOwner());
			}
		}
	}

	if (Character->CombatType == ECombatType::MELEE)
	{
		// TODO
		UE_LOG(LogTemp, Warning, TEXT("%s attacking"), *GetOwner()->GetName());
		// Spawn particle effects
		// Deal damage
	}
}

// Line trace to target
bool UCombat::AttackTrace(FHitResult &Hit, FVector &AttackDirection) 
{
	AController *CharacterController = GetOwnerController();
	if (!CharacterController) {return false;}
		
	// Get character view location and rotation
	FVector CharacterViewLocation;
	FRotator CharacterViewRotation;
	CharacterController->GetPlayerViewPoint(OUT CharacterViewLocation, OUT CharacterViewRotation);

	AttackDirection = CharacterViewRotation.Vector();

	// Line trace from viewpoint and return hit
	FVector TraceEnd = CharacterViewLocation + CharacterViewRotation.Vector() * AttackRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(OUT Hit, CharacterViewLocation, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

// Get character controller for owner of this component
AController* UCombat::GetOwnerController() const
{
	if (!Character){return nullptr;}
	return Character->GetController();
}

