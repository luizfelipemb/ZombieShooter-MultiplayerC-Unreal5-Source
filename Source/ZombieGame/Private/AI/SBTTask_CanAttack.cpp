#include "AI/SBTTask_CanAttack.h"
#include "AI/SAIController.h"

USBTTask_CanAttack::USBTTask_CanAttack()
{
	WaitTime = 2.0f;
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type USBTTask_CanAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TimeElapsed = 0;
	UE_LOG(LogTemp, Warning, TEXT("Starting attack preparation. WaitTime: %f, Initial TimeElapsed: %f"), WaitTime, TimeElapsed);

	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ASAIController* MyController = Cast<ASAIController>(AIController))
		{
			MyController->OnStartPreparingForAttack.Broadcast();
		}
	}

	return EBTNodeResult::InProgress;
}

void USBTTask_CanAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	TimeElapsed += DeltaSeconds;

	if (TimeElapsed >= WaitTime)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void USBTTask_CanAttack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Stopping attack preparation. Final TimeElapsed: %f"), TimeElapsed);

	if (AAIController* AIController = OwnerComp.GetAIOwner())
	{
		if (ASAIController* MyController = Cast<ASAIController>(AIController))
		{
			MyController->OnStopPreparingForAttack.Broadcast();
		}
	}
}
