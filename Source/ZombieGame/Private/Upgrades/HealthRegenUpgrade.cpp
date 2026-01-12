// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrades/HealthRegenUpgrade.h"

#include "SHealthRegenComponent.h"
#include "ZombieGame/SAttributesComponent.h"

void UHealthRegenUpgrade::ApplyUpgrade(AActor* TargetActor, float EffectValue)
{
	if(TargetActor)
	{
		if(!ensure(TargetActor->GetComponentByClass<USAttributesComponent>()))
		{
			return;
		}
		if(auto HealthRegenComponent2 = TargetActor->GetComponentByClass<USHealthRegenComponent>())
		{
			HealthRegenComponent2->AmountPerSecond = EffectValue;
		}
		else if (USHealthRegenComponent* HealthRegenComponent = NewObject<USHealthRegenComponent>(TargetActor))
		{
			HealthRegenComponent->RegisterComponent();
			TargetActor->AddInstanceComponent(HealthRegenComponent);
			HealthRegenComponent->AmountPerSecond = EffectValue;
		}
	}
}
