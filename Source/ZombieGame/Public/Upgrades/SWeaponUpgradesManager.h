// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Upgrade.h"
#include "SWeaponUpgradesManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeChange);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIEGAME_API USWeaponUpgradesManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	USWeaponUpgradesManager();
	TArray<FUpgrade> GetAvailableUpgrades();
	TArray<FUpgrade*> UpgradesChoosed;
	UFUNCTION(BlueprintCallable)
	TArray<FUpgrade> GetCurrentUpgrades() const;
	void IncrementWeaponUpgrade(FName UpgradeType);
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "Events")
	FOnUpgradeChange OnUpgradeChange;
	
protected:
	virtual void BeginPlay() override;
	void InitializeUpgradeData();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Upgrades")
	int MaximumUpgrades = 2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrades")
	UDataTable* UpgradeDataTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Upgrades")
	TMap<FName, FUpgrade> RuntimeUpgrades;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade UI")
	UTexture2D* UpgradeTypeIcon;
};
