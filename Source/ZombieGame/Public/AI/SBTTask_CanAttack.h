// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SBTTask_CanAttack.generated.h"

UCLASS()
class ZOMBIEGAME_API USBTTask_CanAttack : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	USBTTask_CanAttack();
	
	UPROPERTY(EditAnywhere, Category = "Wait")
	float WaitTime;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Wait")
	float TimeElapsed;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override {}
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	
};
