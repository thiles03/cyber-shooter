#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CYBERSHOOTER_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	UGrabber();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPhysicsHandleComponent *PhysicsHandle = nullptr;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInputComponent *Input = nullptr;

	// VARIABLES
	UPROPERTY(EditAnywhere)
	float Reach = 430.f;

	bool IsHolding = false;

	// FUNCTIONS
	void Interact();

	void Grab();

	void Release();

	void FindPhysicsHandle();

	void SetupInputComponent();

	FHitResult GetFirstPhysicsBodyInReach() const;

	FVector GetPlayerInteractPoint() const;

	FVector GetPlayerViewPos() const;
};
