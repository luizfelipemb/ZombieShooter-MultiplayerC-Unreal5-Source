// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthRegenComponent.h"

#include "ZombieGame/SAttributesComponent.h"


USHealthRegenComponent::USHealthRegenComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USHealthRegenComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AttributesComponent = GetOwner()->GetComponentByClass<USAttributesComponent>();
	if (GetOwner())
	{
		AttributesComponent = GetOwner()->GetComponentByClass<USAttributesComponent>();
		GetWorld()->GetTimerManager().SetTimer(
			RegenTimerHandle,
			this,
			&USHealthRegenComponent::RegenerateHealth,
			1.0f,  // Interval (every 1 second)
			true    // Looping
		);
	}
}
void USHealthRegenComponent::RegenerateHealth()
{
	if (AttributesComponent)
	{
		AttributesComponent->ApplyHealthChange(GetOwner(), AmountPerSecond);
	}
}

void USHealthRegenComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
	}
}

