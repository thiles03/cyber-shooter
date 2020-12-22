#include "GameMode_Elimination.h"

void AGameMode_Elimination::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    // Get player controller
    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if (PlayerController)
    {
        PlayerController->GameHasEnded(PawnKilled, false);
    }
}
