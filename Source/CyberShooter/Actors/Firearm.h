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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *Offset;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *Mesh;
};
