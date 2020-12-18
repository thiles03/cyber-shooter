#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Firearm.generated.h"

UCLASS()
class CYBERSHOOTER_API AFirearm : public AActor
{
	GENERATED_BODY()

public:
	AFirearm();

	void Fire();

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem *ImpactEffect;

	// VARIABLES
	UPROPERTY(EditAnywhere)
	float MaxRange = 5000; // in cm

	UPROPERTY(EditAnywhere)
	float Damage = 20.f;
};