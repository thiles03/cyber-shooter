#pragma once

#include "CoreMinimal.h"
#include "Character_Base.h"
#include "Character_Player.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AFirearm;

UCLASS()
class CYBERSHOOTER_API ACharacter_Player : public ACharacter_Base
{
	GENERATED_BODY()

public:
	ACharacter_Player();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent *SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *Camera = nullptr;

	// VARIABLES
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFirearm> FirearmClass;

	AFirearm *Firearm;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotationRate = 50.f;

	// FUNCTIONS
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void LookUp(float AxisValue);

	void LookRight(float AxisValue);

	void Fire();
};
