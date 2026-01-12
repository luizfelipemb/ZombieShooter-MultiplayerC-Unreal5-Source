// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_PistolShoot.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEGAME_API USAction_PistolShoot : public USAction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	bool bShowDebugInfo = false;
	virtual void StartAction_Implementation(AActor* Instigator) override;
};
