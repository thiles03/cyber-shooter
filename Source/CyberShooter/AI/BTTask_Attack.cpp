#include "CyberShooter/AI/BTTask_Attack.h"
#include "AIController.h"
#include "CyberShooter/Characters/Character_Base.h"
#include "CyberShooter/Components/Combat.h"

UBTTask_Attack::UBTTask_Attack() 
{
    NodeName = TEXT("Attack");
}

// Get the AI character owner and call it's attack
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    ACharacter_Base *Character = Cast<ACharacter_Base>(OwnerComp.GetAIOwner()->GetPawn());

    if(!Character)
    {
        return EBTNodeResult::Failed;
    }

    Character->CombatHandler->Attack();

    return EBTNodeResult::Succeeded;
}
