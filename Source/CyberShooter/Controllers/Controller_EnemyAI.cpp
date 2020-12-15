#include "Controller_EnemyAI.h"
#include "Kismet/GameplayStatics.h"

void AController_EnemyAI::BeginPlay() 
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this , 0);
    
    SetFocus(PlayerPawn);
    MoveToActor(PlayerPawn, 200);
}
