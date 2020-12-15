#include "Controller_EnemyAI.h"
#include "Kismet/GameplayStatics.h"

void AController_EnemyAI::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void AController_EnemyAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (LineOfSightTo(PlayerPawn))
    {
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn, AcceptanceRadius);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}
