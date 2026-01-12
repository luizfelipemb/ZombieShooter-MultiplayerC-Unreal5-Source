// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_CloseAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ZombieGame/SAttributesComponent.h"

EBTNodeResult::Type USBTTask_CloseAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (ensure(AIController))
	{
		UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		if (BlackboardComponent == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		USAttributesComponent* AttributesComp = Cast<USAttributesComponent>(
			TargetActor->GetComponentByClass(USAttributesComponent::StaticClass()));
		if (AttributesComp)
		{
			AttributesComp->ApplyHealthChange(OwnerComp.GetOwner(),-20.0f);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

void USBTTask_CloseAttack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	if (TaskResult == EBTNodeResult::Aborted)
	{
		// Logic for when the task is aborted
		UE_LOG(LogTemp, Warning, TEXT("Close attack task aborted!"));
	}
	else if (TaskResult == EBTNodeResult::Succeeded)
	{
		// Logic for successful completion
		UE_LOG(LogTemp, Warning, TEXT("Close attack task succeeded!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Close attack task else!"));
	}
}
