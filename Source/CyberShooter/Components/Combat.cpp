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

float UCombat::GetAttackRange() 
{
	return AttackRange;
}

void UCombat::Attack() 
{
	

	if (Character->CombatType == ECombatType::RANGED)
	{
		// Spawn muzzle VFX
		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Character->GetMesh(), TEXT("MuzzleSocket_Primary"));
		}
		
		// Get the character controller
		APawn *CharacterPawn = Cast<APawn>(GetOwner());
		if (!CharacterPawn) {return;}
		AController *CharacterController = CharacterPawn->GetController();
		if (!CharacterController) {return;}
		
		
		// Get character view location and rotation
		FVector CharacterViewLocation;
		FRotator CharacterViewRotation;
		CharacterController->GetPlayerViewPoint(OUT CharacterViewLocation, OUT CharacterViewRotation);

		// Line trace from viewpoint and return hit
		FVector TraceEnd = CharacterViewLocation + CharacterViewRotation.Vector() * AttackRange;
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetOwner());
		bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, CharacterViewLocation, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1, Params);

		// If Character hit
		if (bSuccess)
		{
			FVector AttackOppositeDirection = -CharacterViewRotation.Vector();
			
			// Spawn impact VFX at hit location
			if (ImpactEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, AttackOppositeDirection.Rotation());
			}

			// Do damage to hit actor
			AActor *HitActor = Hit.GetActor();
			if (HitActor)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, -AttackOppositeDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, CharacterController, GetOwner());
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

bool UCombat::AttackTrace(FHitResult &Hit, FVector &AttackDirection) 
{
	
}

