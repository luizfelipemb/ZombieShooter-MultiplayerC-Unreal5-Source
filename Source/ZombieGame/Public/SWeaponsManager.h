// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SWeaponsManager.generated.h"

class ASWeapon;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None UMETA(DisplayName = "None"),
	Knife UMETA(DisplayName = "Knife"),
	Pistol UMETA(DisplayName = "Pistol"),
	Assault UMETA(DisplayName = "Assault")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponSwitched, ASWeapon*, NewWeapon,int,Slot);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIEGAME_API USWeaponsManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	USWeaponsManager();
	void Init(USkeletalMeshComponent* CharacterMeshComponent);
	void SwitchWeapon(int Slot, bool Forced = false);
	void EquipNewWeapon(TSubclassOf<ASWeapon> NewWeapon);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ASWeapon* GetCurrentWeapon();
	ASWeapon* GetWeaponByType(EWeaponType Type);
	TArray<ASWeapon*>& GetWeaponsInventory();
	UFUNCTION(BlueprintCallable)
	void ApplyWeaponDamage();
	void ShootingButtonPressed();
	void ShootingButtonReleased();
	void ReloadButtonPressed();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,Category="Weapons")
	USkeletalMeshComponent* CharacterMesh = nullptr;
	ASWeapon* CurrentWeapon = nullptr;
	bool bWantToShoot;
	
	UPROPERTY(EditAnywhere,Category="Weapons")
	TArray<TSubclassOf<ASWeapon>> WeaponsStartupInventory;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Weapons")
	TArray<ASWeapon*> WeaponsInventory;
	UPROPERTY(EditDefaultsOnly,Category="Weapons")
	FName SocketNameToAttachWeapon;
	
	int8 currentSlotSelected = 0;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWeaponSwitched OnWeaponSwitched;
};
