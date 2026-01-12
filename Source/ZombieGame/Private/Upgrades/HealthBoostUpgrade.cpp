// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrades/HealthBoostUpgrade.h"
#include "ZombieGame/SAttributesComponent.h"

void UHealthBoostUpgrade::ApplyUpgrade(AActor* TargetActor, float EffectValue)
{
	if(TargetActor)
	{
		TargetActor->GetComponentByClass<USAttributesComponent>()->IncreaseMaxHealth(EffectValue);
		UE_LOG(LogTemp, Log, TEXT("Applying Health Boost: +%f"), EffectValue);
	}
}
