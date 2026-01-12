// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrades/FireRateUpgrade.h"

#include "SWeapon.h"

void UFireRateUpgrade::ApplyUpgrade(AActor* TargetActor, float EffectValue)
{
    if(ASWeapon* Weapon = Cast<ASWeapon>(TargetActor))
    {
        Weapon->FireRate += EffectValue;
    }
}
