#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_Base.generated.h"

UENUM()
enum class ECombatType : uint8
{
	MELEE,
	RANGED,
	PLAYER
};

class UCombat;

UCLASS()
class CYBERSHOOTER_API ACharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// CONSTRUCTOR
	ACharacter_Base();

	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCombat *CombatHandler;

	// VARIABLES
	UPROPERTY(EditDefaultsOnly)
	ECombatType CombatType;

	// FUNCTIONS
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Do damage to the character
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// VARIABLES
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CurrentHealth;
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float MaxSpeed = 600.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetSpeed(float Speed);

private:
	// VARIABLES
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	bool IsDead = false;

	// FUNCTIONS
	void Die();
};
