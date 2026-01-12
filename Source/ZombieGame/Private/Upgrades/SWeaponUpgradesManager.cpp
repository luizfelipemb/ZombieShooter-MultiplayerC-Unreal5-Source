// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrades/SWeaponUpgradesManager.h"

#include "SWeapon.h"

USWeaponUpgradesManager::USWeaponUpgradesManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<FUpgrade> USWeaponUpgradesManager::GetAvailableUpgrades()
{
	TArray<FUpgrade> AvailableUpgrades;

	for (const FUpgrade* UpgradePtr : UpgradesChoosed)
	{
		if (UpgradePtr)
		{
			AvailableUpgrades.Add(*UpgradePtr);
		}
	}
	if(AvailableUpgrades.Num()>=MaximumUpgrades)
	{
		return AvailableUpgrades;
	}

	for (const TPair<FName, FUpgrade>& UpgradePair : RuntimeUpgrades)
	{
		const FUpgrade& Upgrade = UpgradePair.Value;

		if (Upgrade.UpgradeType == EUpgradeType::Weapon && Upgrade.Level < Upgrade.MaxLevel)
		{
			if(AvailableUpgrades.Num() < Upgrade.MaxLevel)
			{
				AvailableUpgrades.Add(Upgrade);
			}
			else
			{
				break;
			}
		}
	}
	return AvailableUpgrades;
}

TArray<FUpgrade> USWeaponUpgradesManager::GetCurrentUpgrades() const
{
	TArray<FUpgrade> AvailableUpgrades;

	for (const TPair<FName, FUpgrade>& UpgradePair : RuntimeUpgrades)
	{
		const FUpgrade& Upgrade = UpgradePair.Value;

		if (Upgrade.UpgradeType == EUpgradeType::Weapon && Upgrade.Level > 0)
		{
			AvailableUpgrades.Add(Upgrade);
		}
	}
	return AvailableUpgrades;
}

void USWeaponUpgradesManager::BeginPlay()
{
	Super::BeginPlay();
	InitializeUpgradeData();
}

void USWeaponUpgradesManager::InitializeUpgradeData()
{
	if (!UpgradeDataTable) return;

	TArray<FUpgrade*> AllRows;
	UpgradeDataTable->GetAllRows(TEXT("Loading Upgrade Data"), AllRows);

	for (FUpgrade* Row : AllRows)
	{
		if (Row && Row->UpgradeType == EUpgradeType::Weapon)
		{
			Row->WeaponType = Cast<ASWeapon>(GetOwner())->WeaponType;
			Row->UpgradeTypeIcon = UpgradeTypeIcon;
			RuntimeUpgrades.Add(Row->UpgradeEffect, *Row);
		}
	}
}

void USWeaponUpgradesManager::IncrementWeaponUpgrade(FName UpgradeType)
{
	FUpgrade* UpgradeRow = RuntimeUpgrades.Find(UpgradeType);
	if (UpgradeRow)
	{
		UpgradesChoosed.Add(UpgradeRow);
		if (UpgradeRow->Level < UpgradeRow->MaxLevel)
		{
			UpgradeRow->Level++;
			UpgradeRow->EffectValue = UpgradeRow->EffectValues.IsValidIndex(UpgradeRow->Level - 1)
				                          ? UpgradeRow->EffectValues[UpgradeRow->Level - 1]
				                          : UpgradeRow->EffectValue;

			// Apply the upgrade effect if the class is set
			if (UpgradeRow->UpgradeEffectClass)
			{
				UUpgradeEffectBase* UpgradeEffect = NewObject<UUpgradeEffectBase>(this, UpgradeRow->UpgradeEffectClass);
				if (UpgradeEffect)
				{
					UpgradeEffect->ApplyUpgrade(GetOwner(), UpgradeRow->EffectValue);
				}
			}

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					5.0f,
					FColor::Green,
					FString::Printf(TEXT("Upgrade %s leveled up to %d"),
					*UpgradeType.ToString(),
					                UpgradeRow->Level)
				);
			}
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					5.0f,
					FColor::Yellow,
					FString::Printf(TEXT("Upgrade %s is already at max level!"),
								*UpgradeType.ToString())
				);
			}
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.0f,
				FColor::Red,
				FString::Printf(TEXT("Upgrade %s not found in runtime data!"),
				                *UpgradeType.ToString())
			);
		}
	}
	OnUpgradeChange.Broadcast();
}
