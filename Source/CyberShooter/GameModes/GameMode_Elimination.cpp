#include "GameMode_Elimination.h"

void AGameMode_Elimination::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    // Get controller of killed pawn
    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    // If it's the player, end the game
    if (PlayerController)
    {
        PlayerController->GameHasEnded(PawnKilled, false);
    }
}
