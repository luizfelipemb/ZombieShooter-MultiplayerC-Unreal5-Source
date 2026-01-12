// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrades/UpgradeEffectBase.h"
#include "MovementSpeedUpgrade.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEGAME_API UMovementSpeedUpgrade : public UUpgradeEffectBase
{
	GENERATED_BODY()
	virtual void ApplyUpgrade(AActor* TargetActor, float EffectValue) override;
};
