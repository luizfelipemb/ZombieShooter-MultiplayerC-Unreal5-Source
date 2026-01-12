// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Upgrade.h"
#include "Blueprint/UserWidget.h"
#include "SUpgradeWidget.generated.h"

UCLASS()
class ZOMBIEGAME_API USUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void Init(const TArray<FUpgrade>& AvailableUpgrades);
};
