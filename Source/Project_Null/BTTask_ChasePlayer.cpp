// BTTask_ChasePlayer.cpp

#include "BTTask_ChasePlayer.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
	NodeName = "Chase Player";
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* AIPawn = AIController->GetPawn();
	if (AIPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if (IsPlayerInRange(AIPawn))
	{
		AIController->MoveToActor(PlayerPawn, 5.0f); // �÷��̾� �߰�, 5.0f�� ���� ��� �ݰ�
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

bool UBTTask_ChasePlayer::IsPlayerInRange(APawn* AICharacter)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return false;
	}

	float Distance = FVector::Dist(AICharacter->GetActorLocation(), PlayerPawn->GetActorLocation());
	return Distance <= 1000.0f; // 1000.0f�� �ν� ����
}
