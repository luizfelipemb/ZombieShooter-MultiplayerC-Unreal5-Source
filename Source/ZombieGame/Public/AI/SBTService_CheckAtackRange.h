// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "SBTService_CheckAtackRange.generated.h"

UCLASS()
class ZOMBIEGAME_API USBTService_CheckAtackRange : public UBTService
{
	GENERATED_BODY()

protected:
	/** Key for storing whether the enemy is in attack range */
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector AttackRangeKey;

	/** Key for storing the adjusted target location */
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector AdjustedTargetLocationKey;

	/** Maximum attack range */
	UPROPERTY(EditAnywhere, Category="AI")
	float Distance = 2000.0f;

	/** The EQS query to find a better follow position */
	UPROPERTY(EditAnywhere, Category="AI")
	UEnvQuery* PositioningQuery;

	/** Stores the BehaviorTreeComponent reference for use in EQS callback */
	UPROPERTY()
	UBehaviorTreeComponent* CachedOwnerComp;

	/** Cooldown time between EQS runs */
	UPROPERTY(EditAnywhere, Category="AI")
	float EQSUpdateInterval = 1.0f; // Update EQS every second

	/** Last time EQS was executed */
	float LastEQSExecutionTime = 0.0f;

	/** Executes the service logic every tick */
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	/** Callback when EQS finishes running */
	void OnQueryCompleted(TSharedPtr<FEnvQueryResult> Result);
};
