#include "Controller_Player.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

// Display win/lose screen and begin restart timer
void AController_Player::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if (bIsWinner)
    {
        UUserWidget *WinScreen = CreateWidget(this, WinScreenClass);

        if (WinScreen)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);

        if (LoseScreen)
        {
            LoseScreen->AddToViewport();
        }
    }
        
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

// Enable/disable player input
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
