#include "Firearm.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define OUT

// CONSTRUCTOR
AFirearm::AFirearm()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Spawn particle FX and handle weapon firing
void AFirearm::Fire()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleSocket")); // Spawn VFX

	// Get the player controller
	APawn *PlayerPawn = Cast<APawn>(GetOwner());
	if (PlayerPawn == nullptr) return;
	AController *PlayerController = PlayerPawn->GetController();
	if (PlayerController == nullptr) return;

	// Get playercamera location and rotation
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	PlayerController->GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);

	// Line trace from viewpoint and return hit
	FVector TraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * MaxRange;
	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, PlayerViewLocation, TraceEnd, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccess)
	{
		// Spawn impact VFX at hit location
		FVector ShotOppositeDirection = -PlayerViewRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotOppositeDirection.Rotation());

		// Do damage to hit actor
		AActor *HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, -ShotOppositeDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, PlayerController, this);
		}
	}
}

