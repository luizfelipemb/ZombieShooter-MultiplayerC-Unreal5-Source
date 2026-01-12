// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrades/WeaponReloadSpeedUpgrade.h"

#include "SWeapon.h"

void UWeaponReloadSpeedUpgrade::ApplyUpgrade(AActor* TargetActor, float EffectValue)
{
	if(ASWeapon* Weapon = Cast<ASWeapon>(TargetActor))
	{
		Weapon->ReloadRate += EffectValue;
	}
}
