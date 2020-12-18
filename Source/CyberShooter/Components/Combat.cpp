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
	UE_LOG(LogTemp, Warning, TEXT("%s attacking"), *GetOwner()->GetName());

	if (Character->CombatType == ECombatType::RANGED)
	{
		// Spawn particle effects
		// Trace bullet
		// If player hit
			// Deal damage
	}

	// If melee and within attack range
		// Spawn particle effects
		// Deal damage
}

