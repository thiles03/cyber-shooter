#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Character_Base.h"
#include "Character_Player.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UTimelineComponent;
class UCurveFloat;
class AFirearm;
class UGrabber;

UCLASS()
class CYBERSHOOTER_API ACharacter_Player : public ACharacter_Base
{
	GENERATED_BODY()

public:
	// CONSTRUCTOR
	ACharacter_Player();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION()
	void TimelineFloatReturn(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent *SpringArm;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UGrabber *Grabber;

	UPROPERTY(VisibleAnywhere, Category = "Timelines", meta = (AllowPrivateAccess = "true"))
	FTimeline FOVTimeline;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Timelines", meta = (AllowPrivateAccess = "true"))
	UCurveFloat *fCurve;

	// VARIABLES
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFirearm> FirearmClass;

	UPROPERTY()
	AFirearm *Firearm;

	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float FOV;

	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float AimFOV;

	UPROPERTY(EditAnywhere, Category = "Timelines", meta = (AllowPrivateAccess = "true"))
	float FOVOffset = 40.f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float AimSpeed = 300.f;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotationRate = 50.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	bool IsAiming = false;

	// FUNCTIONS
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void LookUp(float AxisValue);

	void LookRight(float AxisValue);

	void Aim();

	void ResetAim();

	void Fire();

	void Interact();
};
