#pragma once

#include "CoreMinimal.h"
#include "CyberShooter/Characters/Character_Base.h"
#include "Character_Enemy.generated.h"

class UCombat;

UCLASS()
class CYBERSHOOTER_API ACharacter_Enemy : public ACharacter_Base
{
	GENERATED_BODY()

public:
	// CONSTRUCTOR
	ACharacter_Enemy();

protected:

private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCombat *CombatHandler;

	//VARIABLES


	//FUNCTIONS
};
