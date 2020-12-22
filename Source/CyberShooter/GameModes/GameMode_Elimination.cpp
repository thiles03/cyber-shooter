#include "GameMode_Elimination.h"

void AGameMode_Elimination::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("pawn killed"));
}
