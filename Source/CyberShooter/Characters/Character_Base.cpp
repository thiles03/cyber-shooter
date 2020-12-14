#include "Character_Base.h"

ACharacter_Base::ACharacter_Base()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

// Called every frame
void ACharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacter_Base::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Do damage to the character
float ACharacter_Base::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		Die();
	}
	
	return DamageToApply;
}

void ACharacter_Base::Die() 
{
	IsDead = true;
}

