// Fill out your copyright notice in the Description page of Project Settings.

#include "SUpgradesManager.h"

#include "SWeapon.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieGame/SCharacter.h"

USUpgradesManager::USUpgradesManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USUpgradesManager::BeginPlay()
{
	Super::BeginPlay();
	InitializeUpgradeData();
	XpAttributeComp = GetOwner()->GetComponentByClass<USXpAttribute>();
	if (XpAttributeComp)
	{
		XpAttributeComp->OnLevelChanged.AddDynamic(this, &USUpgradesManager::OnLevelPass);
	}
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

void USUpgradesManager::InitializeUpgradeData()
{
	if (!UpgradeDataTable) return;

	TArray<FUpgrade*> AllRows;
	UpgradeDataTable->GetAllRows(TEXT("Loading Upgrade Data"), AllRows);

	for (FUpgrade* Row : AllRows)
	{
		if (Row && Row->UpgradeType == EUpgradeType::Character)
		{
			Row->UpgradeTypeIcon = UpgradeTypeIcon;
			RuntimeCharacterUpgrades.Add(Row->UpgradeEffect, *Row);
		}
	}
}

TArray<FUpgrade> USUpgradesManager::GetAvailableUpgrades(int Amount)
{
	//TODO: optimize function

	TArray<FUpgrade> AvailableUpgrades;

	//GET CHARACTER UPGRADES
	for (const TPair<FName, FUpgrade>& UpgradePair : RuntimeCharacterUpgrades)
	{
		const FUpgrade& Upgrade = UpgradePair.Value;

		if (Upgrade.UpgradeType == EUpgradeType::Character && Upgrade.Level < Upgrade.MaxLevel)
		{
			AvailableUpgrades.Add(Upgrade);
		}
	}

	//GET WEAPON UPGRADES
	if (USWeaponsManager* WeaponsManager = GetOwner()->GetComponentByClass<USWeaponsManager>())
	{
		for (ASWeapon* WeaponInInventory : WeaponsManager->GetWeaponsInventory())
		{
			USWeaponUpgradesManager* WeaponUpgradeManager = WeaponInInventory->GetComponentByClass<
				USWeaponUpgradesManager>();
			AvailableUpgrades.Append(WeaponUpgradeManager->GetAvailableUpgrades());
		}
	}

	// Shuffle the available upgrades to add randomness
	for (int32 i = AvailableUpgrades.Num() - 1; i > 0; --i)
	{
		int32 RandomIndex = FMath::RandRange(0, i);
		AvailableUpgrades.Swap(i, RandomIndex);
	}

	if (AvailableUpgrades.Num() > Amount)
	{
		AvailableUpgrades.SetNum(Amount);
	}

	return AvailableUpgrades;
}

void USUpgradesManager::OnLevelPass(int level)
{
	if (PlayerController && !TurnOffUpgrades)
	{
		// Pause the game
		PlayerController->SetPause(true);
		PlayerController->SetInputMode(FInputModeGameAndUI());
		WaitingForUpgradeSelection = true;

		UpgradeSelectionWidget = CreateWidget<USUpgradeWidget>(PlayerController, UpgradeSelectionWidgetClass);
		if (UpgradeSelectionWidget)
		{
			PlayerController->bShowMouseCursor = true;
			UpgradeSelectionWidget->AddToViewport();
			Cast<USUpgradeWidget>(UpgradeSelectionWidget)->Init(GetAvailableUpgrades(3));
		}
	}
}

void USUpgradesManager::SelectUpgrade(FUpgrade UpgradeToSelect)
{
	UE_LOG(LogTemp, Warning, TEXT("Select Upgrade Type"));
	WaitingForUpgradeSelection = false;
	PlayerController->SetPause(false);
	PlayerController->bShowMouseCursor = false;
	switch (UpgradeToSelect.UpgradeType)
	{
	case EUpgradeType::Character:
		{
			IncrementCharacterUpgrade(UpgradeToSelect.UpgradeEffect);
		}
	case EUpgradeType::Weapon:
		{
			if(ASWeapon* Weapon = GetOwner()->GetComponentByClass<USWeaponsManager>()->GetWeaponByType(UpgradeToSelect.WeaponType))
			{
				Weapon->GetComponentByClass<USWeaponUpgradesManager>()->IncrementWeaponUpgrade(UpgradeToSelect.UpgradeEffect);
			}
			
			UE_LOG(LogTemp, Warning, TEXT("Select Upgrade Type"));
		}
	}

	if (UpgradeSelectionWidget && UpgradeSelectionWidget->IsInViewport())
	{
		UpgradeSelectionWidget->RemoveFromParent();
		PlayerController->bShowMouseCursor = false;
	}
}

void USUpgradesManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USUpgradesManager::IncrementCharacterUpgrade(FName UpgradeType)
{
	FUpgrade* UpgradeRow = RuntimeCharacterUpgrades.Find(UpgradeType);

	if (UpgradeRow)
	{
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
}
