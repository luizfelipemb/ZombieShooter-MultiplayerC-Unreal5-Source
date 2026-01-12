// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZombieGame/SAttributesComponent.h"
#include "SHealthRegenComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIEGAME_API USHealthRegenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USHealthRegenComponent();
	float AmountPerSecond;
	
protected:
	virtual void BeginPlay() override;
	void RegenerateHealth();
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	USAttributesComponent* AttributesComponent;
	FTimerHandle RegenTimerHandle;
};
