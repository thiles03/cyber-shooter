#include "Controller_EnemyAI.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CyberShooter/Characters/Character_Enemy.h"

void AController_EnemyAI::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehaviorTree)
    {
        RunBehaviorTree(AIBehaviorTree);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AController_EnemyAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AController_EnemyAI::IsDead() const
{
    ACharacter_Enemy *ControlledEnemy = Cast<ACharacter_Enemy>(GetPawn());

    if(ControlledEnemy)
    {
        return true;
        
    }

    return true;
}