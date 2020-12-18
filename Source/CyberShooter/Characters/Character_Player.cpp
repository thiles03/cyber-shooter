#include "Character_Player.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "CyberShooter/Actors/Firearm.h"
#include "CyberShooter/Components/Grabber.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Set default values
ACharacter_Player::ACharacter_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));
}

// Called when the game starts or when spawned
void ACharacter_Player::BeginPlay()
{
	Super::BeginPlay();

	if (fCurve)
	{
		SetupTimeline();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No float curve on %s"), *GetOwner()->GetName());
	}
}

// Called every frame
void ACharacter_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FOVTimeline.TickTimeline(DeltaTime);

	if (IsAiming && GetVelocity().Size() > 0 || IsAttacking)
	{
		RotateActorToView();
	}
}

// Bind functionality to input
void ACharacter_Player::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_Player::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_Player::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacter_Player::LookUp);
	PlayerInputComponent->BindAxis("LookRightRate", this, &ACharacter_Player::LookRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	// Interaction
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACharacter_Player::Interact);

	// Combat
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACharacter_Player::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACharacter_Player::AimReset);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACharacter_Player::Attack);
	PlayerInputComponent->BindAction("Weapon1", IE_Pressed, this, &ACharacter_Player::WeaponOne);
	PlayerInputComponent->BindAction("Weapon2", IE_Pressed, this, &ACharacter_Player::WeaponTwo);
}

// Aim weapon
void ACharacter_Player::Aim()
{
	IsAiming = true;
	ACharacter_Base::SetSpeed(AimSpeed);
	FOVTimeline.Play();
}

// Stop aiming
void ACharacter_Player::AimReset()
{
	IsAiming = false;
	ACharacter_Base::SetSpeed(MaxSpeed);
	FOVTimeline.Reverse();
}

// Fire weapon
void ACharacter_Player::Attack()
{
	if (Firearm && !IsAttacking)
	{
		IsAttacking = true;
		Firearm->Fire();
	}
}

// Stop firing
void ACharacter_Player::AttackStop()
{
	IsAttacking = false;
}

// Interact
void ACharacter_Player::Interact()
{
	if (Grabber)
	{
		Grabber->Interact();
	}
}

// Look right gamepad
void ACharacter_Player::LookRight(float AxisValue)
{
	AddControllerYawInput(RotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

// Look up gamepad
void ACharacter_Player::LookUp(float AxisValue)
{
	AddControllerPitchInput(RotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

// Move forward
void ACharacter_Player::MoveForward(float AxisValue)
{
	FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, AxisValue);
}

// Move right
void ACharacter_Player::MoveRight(float AxisValue)
{
	FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, AxisValue);
}

// Rotate player to face camera direction
void ACharacter_Player::RotateActorToView() 
{
	AController *PlayerController = GetController();

	// Get player camera location and rotation
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	PlayerController->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);

	// Rotate player to face camera direction
	FRotator TargetRotation = FRotator(GetActorRotation().Roll, PlayerViewRotation.Yaw, GetActorRotation().Pitch);
	FRotator InterpRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, FApp::GetDeltaTime(), RotateActorInterp);
	SetActorRotation(InterpRotation);
}

// Timeline for aiming zoom
void ACharacter_Player::SetupTimeline() 
{
		// Bind timeline delegate and add float track
		TimelineProgress.BindUFunction(this, FName("TimelineFloatReturn"));
		FOVTimeline.AddInterpFloat(fCurve, TimelineProgress);

		// Setting FOVs
		FOV = Camera->FieldOfView;
		AimFOV = FOV - FOVOffset;

		// Setting timeline's settings before start
		FOVTimeline.SetLooping(false);
}

// FOV Timeline
void ACharacter_Player::TimelineFloatReturn(float Value) 
{
	Camera->SetFieldOfView(FMath::Lerp(FOV, AimFOV, Value));
}

// Default pistol
void ACharacter_Player::WeaponOne() 
{
	CombatType = ECombatType::RANGED;
}

// Secondary pistol
void ACharacter_Player::WeaponTwo() 
{
	CombatType = ECombatType::PLAYER;
	
	// Hide default pistol
	GetMesh()->HideBoneByName(TEXT("pistol"), EPhysBodyOp::PBO_None);

	// Spawn selected firearm class in the world
	Firearm = GetWorld()->SpawnActor<AFirearm>(FirearmClass);
	// Attach firearm to character mesh
	Firearm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocketRight"));
	Firearm->SetOwner(this);
}

