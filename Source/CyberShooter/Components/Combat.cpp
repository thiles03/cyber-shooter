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


// Called every frame
void UCombat::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

