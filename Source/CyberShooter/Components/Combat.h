#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Combat.generated.h"

class ACharacter_Base;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CYBERSHOOTER_API UCombat : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombat();

	void Attack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// VARIABLES
	UPROPERTY()
	ACharacter_Base *Character;

	//FUNCTIONS
		
};
