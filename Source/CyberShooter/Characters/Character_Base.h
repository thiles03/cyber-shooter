#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character_Base.generated.h"

UCLASS()
class CYBERSHOOTER_API ACharacter_Base : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacter_Base();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Do damage to the character
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float MaxSpeed = 600.f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetSpeed(float Speed);

private:
	// VARIABLES
	UPROPERTY(EditDefaultsOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	bool IsDead = false;

	// FUNCTIONS
	void Die();
};
