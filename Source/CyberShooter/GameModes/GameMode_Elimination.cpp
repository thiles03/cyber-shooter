#include "GameMode_Elimination.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "CyberShooter/Controllers/Controller_EnemyAI.h"

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

    for (AController_EnemyAI *AIController : TActorRange<AController_EnemyAI>(GetWorld()))
    {
        bool IsDead = AIController->IsDead();
        if (!IsDead)
        {
            return;
        }
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
