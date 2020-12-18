#include "CyberShooter/AI/BTTask_Shoot.h"


UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetAIOwner();

    return EBTNodeResult::Succeeded;
}
