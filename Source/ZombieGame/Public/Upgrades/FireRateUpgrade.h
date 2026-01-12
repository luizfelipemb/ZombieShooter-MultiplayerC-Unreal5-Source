// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrades/UpgradeEffectBase.h"
#include "FireRateUpgrade.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEGAME_API UFireRateUpgrade : public UUpgradeEffectBase
{
	GENERATED_BODY()
protected:
	virtual void ApplyUpgrade(AActor* TargetActor, float EffectValue) override;
};
