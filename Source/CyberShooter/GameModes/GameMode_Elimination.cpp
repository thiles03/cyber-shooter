#include "GameMode_Elimination.h"

void AGameMode_Elimination::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if (PlayerController)
    {
        PlayerController->GameHasEnded(nullptr, false);
    }
}
