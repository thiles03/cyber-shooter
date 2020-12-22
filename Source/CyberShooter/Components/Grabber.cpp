#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	
	// If an object is grabbed, move it
	if (!PhysicsHandle) {return;}
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayerInteractPoint());
	}
}

// Check for physics handle component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle on %s!"), *GetOwner()->GetName());
	}
}

// Returns line trace end
FVector UGrabber::GetPlayerInteractPoint() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	FVector LineTraceEnd = PlayerViewpointLocation + FVector(PlayerViewpointRotation.Vector() * Reach);

	return LineTraceEnd;
}

// Returns player viewpoint world position
FVector UGrabber::GetPlayerViewPos() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);

	return PlayerViewpointLocation;
}

// Returns physics body hit by line trace
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerViewPos(),
		GetPlayerInteractPoint(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}

// If NOT holding something, grab it. Else, release
void UGrabber::Interact()
{
	if (!IsHolding)
	{
		Grab();
	}
	else
	{
		Release();
	}
	
}

// Grab hit physics body
void UGrabber::Grab()
{
	FHitResult HitResult =  GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* GrabbedComponent = HitResult.GetComponent();

	// If hit something, attach physics handle
	if(HitResult.GetActor())
	{
		if (!PhysicsHandle) {return;}
		PhysicsHandle->GrabComponentAtLocation(
			GrabbedComponent,
			NAME_None,
			GetPlayerInteractPoint()
		);
		IsHolding = true;
	}
}

// Release grabbed physics body
void UGrabber::Release()
{
	if (!PhysicsHandle || IsHolding == false) {return;}
	PhysicsHandle->ReleaseComponent();
	IsHolding = false;
}