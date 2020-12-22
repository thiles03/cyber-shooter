#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_Base.generated.h"

UCLASS()
class CYBERSHOOTER_API AGameMode_Base : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn *PawnKilled);
};
