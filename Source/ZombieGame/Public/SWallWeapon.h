// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieGame/SGameplayInterface.h"
#include "SWallWeapon.generated.h"

class ASWeapon;

UCLASS()
class ZOMBIEGAME_API ASWallWeapon : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
public:	
	ASWallWeapon();
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
protected:
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASWeapon> WeaponToGive;
};
