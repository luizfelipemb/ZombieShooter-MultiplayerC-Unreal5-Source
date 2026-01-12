// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "AI/SBTService_CheckAtackRange.h"

void USBTService_CheckAtackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!ensure(BlackboardComponent)) return;

	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
	if (!TargetActor) return;

	AAIController* MyController = OwnerComp.GetAIOwner();
	if (!ensure(MyController)) return;

	APawn* AIPawn = MyController->GetPawn();
	if (!ensure(AIPawn)) return;

	// Store reference to OwnerComp so it can be accessed in the callback
	CachedOwnerComp = &OwnerComp;

	// Check if enough time has passed since the last EQS execution
	LastEQSExecutionTime += DeltaSeconds;
	if (LastEQSExecutionTime >= EQSUpdateInterval)
	{
		// Run EQS Query to find a good follow position
		if (PositioningQuery)
		{
			FEnvQueryRequest QueryRequest(PositioningQuery, AIPawn);
			QueryRequest.Execute(EEnvQueryRunMode::SingleResult, this, &USBTService_CheckAtackRange::OnQueryCompleted);
		}

		// Reset the timer
		LastEQSExecutionTime = 0.0f;
	}
}

void USBTService_CheckAtackRange::OnQueryCompleted(TSharedPtr<FEnvQueryResult> Result)
{
	if (Result->IsSuccessful() && CachedOwnerComp)
	{
		FVector BestPosition = Result->GetItemAsLocation(0);
		UBlackboardComponent* BlackboardComponent = CachedOwnerComp->GetBlackboardComponent();
		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsVector(AdjustedTargetLocationKey.SelectedKeyName, BestPosition);
		}
	}
}
