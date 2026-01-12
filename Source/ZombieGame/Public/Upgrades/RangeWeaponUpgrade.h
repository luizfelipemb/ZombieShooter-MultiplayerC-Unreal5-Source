// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrades/UpgradeEffectBase.h"
#include "RangeWeaponUpgrade.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEGAME_API URangeWeaponUpgrade : public UUpgradeEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyUpgrade(AActor* TargetActor, float EffectValue) override;
};
