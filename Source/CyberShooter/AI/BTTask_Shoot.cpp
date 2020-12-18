#include "CyberShooter/AI/BTTask_Shoot.h"
#include "AIController.h"
#include "CyberShooter/Characters/Character_Base.h"
#include "CyberShooter/Components/Combat.h"

UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    ACharacter_Base *Character = Cast<ACharacter_Base>(OwnerComp.GetAIOwner()->GetPawn());

    if(Character == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Character->CombatHandler->Attack();

    return EBTNodeResult::Succeeded;
}
