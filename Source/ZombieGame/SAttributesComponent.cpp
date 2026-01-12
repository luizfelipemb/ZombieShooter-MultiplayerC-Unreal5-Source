// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributesComponent.h"
#include "SActionComponent.h"
#include "SXpAttribute.h"
#include "SXpGiver.h"

USAttributesComponent::USAttributesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = MaxHealth;
}

bool USAttributesComponent::IsAlive()
{
	return Health > 0;
}

void USAttributesComponent::IncreaseMaxHealth(float IncreasedAmount)
{
	MaxHealth += IncreasedAmount;
	OnHealthChanged.Broadcast(nullptr, this, Health, 0,MaxHealth);
}

bool USAttributesComponent::ApplyHealthChange(AActor* Instigator, float Delta)
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		USActionComponent* ActionComponent = Owner->FindComponentByClass<USActionComponent>();
		if (ActionComponent && ActionComponent->GameplayTags.HasTag(
			FGameplayTag::RequestGameplayTag(FName("buffs.armor"))))
		{
			Delta *= 0.5f;
		}
	}

	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta,MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	
	if(!IsAlive() && Instigator)
	{
		USXpGiver* XpGiver = Cast<USXpGiver>(Owner->GetComponentByClass(USXpGiver::StaticClass()));
		USXpAttribute* XpComp = Cast<USXpAttribute>(Instigator->GetComponentByClass(USXpAttribute::StaticClass()));
		if (XpGiver && XpComp)
		{
			XpComp->AddXp(XpGiver->XpToGive);
		}
	}

	return true;
}
