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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
	float Damage = 10;
};