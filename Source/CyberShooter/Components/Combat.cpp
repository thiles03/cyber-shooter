#include "CyberShooter/Components/Combat.h"

// Constructor
UCombat::UCombat()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCombat::BeginPlay()
{
	Super::BeginPlay();
}

void UCombat::Attack() 
{
	UE_LOG(LogTemp, Warning, TEXT("%s attacking"), *GetOwner()->GetName());

	// If ranged
		// Spawn particle effects
		// Trace bullet
		// If player hit
			// Deal damage

	// If melee and within attack range
		// Spawn particle effects
		// Deal damage
}

