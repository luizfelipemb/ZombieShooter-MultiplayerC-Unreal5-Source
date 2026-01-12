// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SXpGiver.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIEGAME_API USXpGiver : public UActorComponent
{
	GENERATED_BODY()

public:	
	USXpGiver();
	UPROPERTY(EditDefaultsOnly)
	float XpToGive =  50;
};
