#include "Firearm.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values
AFirearm::AFirearm()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AFirearm::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFirearm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Spawn particle FX and handle weapon firing
void AFirearm::Fire()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleSocket")); // Spawn VFX

	// Get the weapon owner's controller
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;
	AController *OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	// Get playercamera location and rotation
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	OwnerController->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);

	// Line trace from viewpoint and return hit
	FVector TraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * MaxRange;
	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, PlayerViewLocation, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccess)
	{
		// Spawn impact VFX at hit location
		FVector ShotDirection = -PlayerViewRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());

		// Do damage to hit actor
		AActor *HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}

	}
}