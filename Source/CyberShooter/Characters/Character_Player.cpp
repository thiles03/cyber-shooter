#include "Character_Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

    // Combat
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACharacter_Player::Fire);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &ACharacter_Player::CheckFire);
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


// Fire weapon
void ACharacter_Player::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("fire"));
	IsFiring = true;
}

// Stop firing weapon
void ACharacter_Player::CheckFire()
{
	UE_LOG(LogTemp, Warning, TEXT("check fire"));
	IsFiring = false;
}