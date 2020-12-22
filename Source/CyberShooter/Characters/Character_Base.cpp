#include "Character_Base.h"
#include "Components/CapsuleComponent.h"
#include "CyberShooter/Components/Combat.h"
#include "CyberShooter/GameModes/GameMode_Base.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacter_Base::ACharacter_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	CombatHandler = CreateDefaultSubobject<UCombat>(TEXT("Combat Handler"));
}

// Called when the game starts or when spawned
void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
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
float ACharacter_Base::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(CurrentHealth, DamageToApply);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0 && !IsDead)
	{
		Die();
	}

	return DamageToApply;
}

// Death handler
void ACharacter_Base::Die()
{
	IsDead = true;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AGameMode_Base *GameMode = GetWorld()->GetAuthGameMode<AGameMode_Base>();

	if (GameMode)
	{
		GameMode->PawnKilled(this);
	}
	
	DetachFromControllerPendingDestroy();
}

// Set move speed
void ACharacter_Base::SetSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}
