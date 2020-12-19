#include "CyberShooter/AI/BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    Ownercomp.GetBlackboardComponent();
}
