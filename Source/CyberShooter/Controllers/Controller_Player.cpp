#include "Controller_Player.h"
#include "TimerManager.h"

void AController_Player::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel(RestartDelay));
}
