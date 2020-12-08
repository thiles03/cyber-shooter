#include "Character_Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CyberShooter/Actors/Firearm.h"
#include "CyberShooter/Components/Grabber.h"

// Set default values
ACharacter_Player::ACharacter_Player()
{
	PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ACharacter_Player::BeginPlay()
{
	Super::BeginPlay();

	// Hide default pistol
	GetMesh()->HideBoneByName(TEXT("pistol"), EPhysBodyOp::PBO_None);

	// Spawn selected firearm class in the world
	Firearm = GetWorld()->SpawnActor<AFirearm>(FirearmClass);
	// Attach firearm to character mesh
	Firearm->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform , TEXT("WeaponSocketRight"));
	Firearm->SetOwner(this);

	// Find Grabber component
	Grabber = FindComponentByClass<UGrabber>();
}

// Called every frame
void ACharacter_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Bind functionality to input
void ACharacter_Player::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Movement
    PlayerInputComponent->BindAxis("MoveForward", this, &ACharacter_Player::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_Player::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACharacter_Player::LookUp);
    PlayerInputComponent->BindAxis("LookRightRate", this, &ACharacter_Player::LookRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	// Interaction
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACharacter_Player::Interact);

    // Combat
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACharacter_Player::Fire);
}

// Move forward
void ACharacter_Player::MoveForward(float AxisValue) 
{
    AddMovementInput(GetActorForwardVector() * AxisValue);
}

// Move right
void ACharacter_Player::MoveRight(float AxisValue) 
{
    AddMovementInput(GetActorRightVector() * AxisValue);
}

// Look up
void ACharacter_Player::LookUp(float AxisValue) 
{
	AddControllerPitchInput(RotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

// Look right
void ACharacter_Player::LookRight(float AxisValue) 
{
	AddControllerYawInput(RotationRate * AxisValue * GetWorld()->GetDeltaSeconds());
}

// Fire weapon
void ACharacter_Player::Fire()
{
	Firearm->Fire();
}

// Interact
void ACharacter_Player::Interact()
{
	if (Grabber)
	{
		Grabber->Interact();
	}
}