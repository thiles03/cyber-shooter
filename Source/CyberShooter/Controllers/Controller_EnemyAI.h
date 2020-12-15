#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Controller_EnemyAI.generated.h"

UCLASS()
class CYBERSHOOTER_API AController_EnemyAI : public AAIController
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

private:
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree *AIBehaviorTree;
};
