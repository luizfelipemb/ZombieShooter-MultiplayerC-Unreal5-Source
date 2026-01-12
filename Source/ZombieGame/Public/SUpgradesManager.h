// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SXpAttribute.h"
#include "Components/ActorComponent.h"
#include "Upgrades/SUpgradeWidget.h"
#include "Upgrades/Upgrade.h"
#include "Upgrades/UpgradeEffectBase.h"
#include "ZombieGame/SAttributesComponent.h"
#include "SUpgradesManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIEGAME_API USUpgradesManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	USUpgradesManager();
	UFUNCTION(BlueprintCallable)
	void SelectUpgrade(FUpgrade UpgradeToSelect);
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnLevelPass(int level);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void IncrementCharacterUpgrade(FName UpgradeType);
	void InitializeUpgradeData();
	TArray<FUpgrade> GetAvailableUpgrades(int Amount);
protected:
	USXpAttribute* XpAttributeComp;
	APlayerController* PlayerController;
	
	UPROPERTY(EditAnywhere, Category="Settings")
	bool TurnOffUpgrades = false;
	bool WaitingForUpgradeSelection = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrades")
	UDataTable* UpgradeDataTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Upgrades")
	TMap<FName, FUpgrade> RuntimeCharacterUpgrades;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USUpgradeWidget> UpgradeSelectionWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade UI")
	UTexture2D* UpgradeTypeIcon;
	UUserWidget* UpgradeSelectionWidget;
};
