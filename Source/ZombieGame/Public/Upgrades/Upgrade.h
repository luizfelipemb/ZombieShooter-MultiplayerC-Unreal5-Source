#pragma once
#include <vector>

#include "SWeaponsManager.h"
#include "Upgrade.generated.h"

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	Character,
	Weapon,
};

USTRUCT(BlueprintType)
struct FUpgrade : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade Data")
	EUpgradeType UpgradeType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade Data")
	FName UpgradeEffect;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Upgrade Data")
	EWeaponType WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrade Data")
	TSubclassOf<class UUpgradeEffectBase> UpgradeEffectClass;
	UPROPERTY(EditInstanceOnly,BlueprintReadOnly, Category = "Upgrade Data")
	int Level = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade Data")
	int MaxLevel = 5;
	UPROPERTY(EditInstanceOnly,BlueprintReadOnly, Category = "Upgrade Data")
	float EffectValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade Data")
	TArray<float> EffectValues;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade UI")
	FString UpgradeDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade UI")
	UTexture2D* UpgradeEffectIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade UI")
	UTexture2D* UpgradeTypeIcon;
};
