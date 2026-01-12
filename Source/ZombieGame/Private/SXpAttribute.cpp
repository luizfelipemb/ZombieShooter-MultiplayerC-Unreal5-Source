// Fill out your copyright notice in the Description page of Project Settings.


#include "SXpAttribute.h"

#include "ZombieGame/SCharacter.h"

USXpAttribute::USXpAttribute()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USXpAttribute::AddXp(float Amount)
{
	Xp += Amount;
	if(Xp >= XpToNextLevel && ensure(XpCurve))
	{
		Level++;
		OnLevelChanged.Broadcast(Level);
		Xp = Xp-XpToNextLevel;
		XpToNextLevel = XpCurve->GetFloatValue(Level+1);
	}
	OnXPChanged.Broadcast(this,Xp,XpToNextLevel,Amount,Level);
}

void USXpAttribute::BeginPlay()
{
	Super::BeginPlay();
	XpToNextLevel = XpCurve->GetFloatValue(Level+1);
	OnXPChanged.Broadcast(this,Xp,XpToNextLevel,0,Level);
}