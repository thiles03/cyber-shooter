#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Controller_Player.generated.h"

UCLASS()
class CYBERSHOOTER_API AController_Player : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	void SetPlayerEnabledState(bool IsEnabled);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle RestartTimer;
};
