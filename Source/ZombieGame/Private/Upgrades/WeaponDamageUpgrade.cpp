// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrades/WeaponDamageUpgrade.h"

#include "SWeapon.h"

void UWeaponDamageUpgrade::ApplyUpgrade(AActor* TargetActor, float EffectValue)
{
	if(ASWeapon* Weapon = Cast<ASWeapon>(TargetActor))
	{
		Weapon->WeaponDamage -= EffectValue;
	}
}
