// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrades/UpgradeEffectBase.h"
#include "HealthBoostUpgrade.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class ZOMBIEGAME_API UHealthBoostUpgrade : public UUpgradeEffectBase
{
	GENERATED_BODY()
public:
	virtual void ApplyUpgrade(AActor* TargetActor, float EffectValue) override;
};
