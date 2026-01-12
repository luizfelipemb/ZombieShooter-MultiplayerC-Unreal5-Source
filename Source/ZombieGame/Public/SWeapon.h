// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "Upgrades/SWeaponUpgradesManager.h"
#include "ZombieGame/SAttributesComponent.h"
#include "ZombieGame/SCharacter.h"
#include "SWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnWeaponReload,
	EWeaponType, NewWeaponType,int,AmmoInWeapon,int,AmmoInPockets,
	float,ReloadRate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWeaponShoot,
	EWeaponType,WeaponType,float,FireRate = 1,int, AmmoInWeapon);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponStopShoot);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponUpdateAmmo,
	int, AmmoInWeapon,int,AmmoInPockets);

UCLASS()
class ZOMBIEGAME_API ASWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASWeapon();
	
	virtual void StartShoot();
	virtual void StopShoot();
	void FindClosestTarget();
	void ApplyDamageToTarget();
	void OnEquipped();
	bool IsShooting() const {return bShooting;}
	void StartReload();
	UFUNCTION(BlueprintCallable)
	void CompleteReload();
protected:
	UFUNCTION(BlueprintNativeEvent)
	void ShootEffect(AActor* targetActor);
	UFUNCTION()
	void OnCollisionMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    	                                 const FHitResult& SweepResult);
	UFUNCTION()
	void OnCollisionMeshEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    	                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void ResetShootCooldown();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType = EWeaponType::None;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int AmmoMaxCapacity = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int AmmoInWeapon = 5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int AmmoInPockets = 20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float FireRate = 1;
	void ApplyRangeMultiplier(FVector Multiplier);
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float ReloadRate = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float WeaponDamage = -20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float WeaponAntiSpamCooldown = 0.5f;
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "Events")
	FOnWeaponShoot OnWeaponShoot;
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "Events")
	FOnWeaponStopShoot OnWeaponStopShoot;
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "Events")
	FOnWeaponReload OnWeaponReloadStart;
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "Events")
	FOnWeaponReload OnWeaponReloadFinished;
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "Events")
	FOnWeaponUpdateAmmo OnWeaponUpdateAmmo;

protected:
	bool bCanShoot = false;
	bool bShooting = false;
	bool bReadyToShoot = false;
	FTimerHandle CooldownTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* CollisionDetectionMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> TargetActors;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* CurrentTarget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USWeaponUpgradesManager* UpgradesManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTexture2D* WeaponIcon;
};
