// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAIController.generated.h"

class UBehaviorTree;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartPreparingForAttackEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopPreparingForAttackEvent);

UCLASS()
class ZOMBIEGAME_API ASAIController : public AAIController
{
	GENERATED_BODY()
public:
	// Events to start and stop preparation
	UPROPERTY(BlueprintAssignable, Category = "Attack Events")
	FOnStartPreparingForAttackEvent OnStartPreparingForAttack;

	UPROPERTY(BlueprintAssignable, Category = "Attack Events")
	FOnStopPreparingForAttackEvent OnStopPreparingForAttack;

protected:
	UFUNCTION(BlueprintCallable, Category = "AI")
	void ApplyAttack() const;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
	virtual void BeginPlay() override;
};
