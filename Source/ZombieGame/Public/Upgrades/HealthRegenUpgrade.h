// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrades/UpgradeEffectBase.h"
#include "HealthRegenUpgrade.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEGAME_API UHealthRegenUpgrade : public UUpgradeEffectBase
{
public:
	virtual void ApplyUpgrade(AActor* TargetActor, float EffectValue) override;

private:
	GENERATED_BODY()
};
