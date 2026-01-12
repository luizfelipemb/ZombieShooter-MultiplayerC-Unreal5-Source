// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrades/RangeWeaponUpgrade.h"

#include "SWeapon.h"

void URangeWeaponUpgrade::ApplyUpgrade(AActor* TargetActor, float EffectValue)
{
	if(ASWeapon* Weapon = Cast<ASWeapon>(TargetActor))
	{
		Weapon->ApplyRangeMultiplier(FVector(1,1,EffectValue));
	}
}
