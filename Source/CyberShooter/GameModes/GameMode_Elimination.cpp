#include "GameMode_Elimination.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

void AGameMode_Elimination::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    // Get controller of killed pawn
    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    // If it's the player, end the game
    if (PlayerController)
    {
        EndGame(false);
    }
}

// Handle win/lose
void AGameMode_Elimination::EndGame(bool bIsPlayerWinner) 
{
    // Iterate over all characters
    for (AController *Controller : TActorRange<AController>(GetWorld()))
    {
        // Notify each actor controller if it is the winner/loser
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
