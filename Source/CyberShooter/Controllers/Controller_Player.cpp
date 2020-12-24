#include "Controller_Player.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AController_Player::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

    UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);
    if (LoseScreen)
    {
        LoseScreen->AddToViewport();
    }
}

void AController_Player::SetPlayerEnabledState(bool IsEnabled)
{
    if (IsEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
}
