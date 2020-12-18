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

void UCombat::Attack() 
{
	

	if (Character->CombatType == ECombatType::RANGED)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Character->GetMesh(), TEXT("MuzzleSocket_Primary")); // Spawn muzzle VFX
		// Trace bullet
		// If player hit
			// Deal damage
	}

	if (Character->CombatType == ECombatType::MELEE)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s attacking"), *GetOwner()->GetName());
		// Spawn particle effects
		// Deal damage
	}
}

