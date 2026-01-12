// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeaponsManager.h"

#include "SWeapon.h"

USWeaponsManager::USWeaponsManager()
{
	//PrimaryComponentTick.bCanEverTick = true;
}

void USWeaponsManager::Init(USkeletalMeshComponent* CharacterMeshComponent)
{
	 CharacterMesh = CharacterMeshComponent;
}

void USWeaponsManager::BeginPlay()
{
	Super::BeginPlay();
	
	for (TSubclassOf<ASWeapon> WeaponClass : WeaponsStartupInventory)
	{
		if (WeaponClass)
		{
			ASWeapon* NewWeapon = GetWorld()->SpawnActor<ASWeapon>(WeaponClass);
			if (NewWeapon)
			{
				WeaponsInventory.Add(NewWeapon);
				UE_LOG(LogTemp, Log, TEXT("Spawned weapon: %s"), *NewWeapon->GetName());
			}
		}
	}

	if (WeaponsInventory.Num() > 0)
	{
		SwitchWeapon(0);
	}
}

void USWeaponsManager::EquipNewWeapon(TSubclassOf<ASWeapon> NewWeapon)
{
	WeaponsInventory[currentSlotSelected] = GetWorld()->SpawnActor<ASWeapon>(NewWeapon);
	SwitchWeapon(currentSlotSelected,true);
}

ASWeapon* USWeaponsManager::GetCurrentWeapon()
{
	return CurrentWeapon;
}

ASWeapon* USWeaponsManager::GetWeaponByType(EWeaponType Type)
{
	for (auto Weapon : WeaponsInventory)
	{
		if (Weapon && Weapon->WeaponType == Type)
		{
			return Weapon;
		}
	}
	return nullptr;
}

TArray<ASWeapon*>& USWeaponsManager::GetWeaponsInventory()
{
	return WeaponsInventory;
}

void USWeaponsManager::ApplyWeaponDamage()
{
	if(CurrentWeapon)
	{
		CurrentWeapon->ApplyDamageToTarget();
	}
}

void USWeaponsManager::ShootingButtonPressed()
{
	if(CurrentWeapon)
	{
		bWantToShoot = true;
		CurrentWeapon->StartShoot();
	}
}

void USWeaponsManager::ShootingButtonReleased()
{
	if(CurrentWeapon)
	{
		bWantToShoot = false;
		CurrentWeapon->StopShoot();
	}
}

void USWeaponsManager::ReloadButtonPressed()
{
	UE_LOG(LogTemp, Log, TEXT("Reloading"));
	CurrentWeapon->StartReload();
}

void USWeaponsManager::SwitchWeapon(int Slot, bool Forced)
{
	if(currentSlotSelected == Slot && !Forced)
	{
		return;
	}
	if (!WeaponsInventory.IsValidIndex(Slot))
    	{
    		return;
    	}
	
	if(CurrentWeapon)
	{
		CurrentWeapon->StopShoot();
		CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		CurrentWeapon->SetActorEnableCollision(false);
		CurrentWeapon->SetActorHiddenInGame(true);
	}
	
	ASWeapon* NewWeapon = WeaponsInventory[Slot];
	CurrentWeapon = NewWeapon;
	if(NewWeapon && CharacterMesh)
	{
		NewWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, SocketNameToAttachWeapon);
		CurrentWeapon->SetActorEnableCollision(true);
		NewWeapon->SetActorHiddenInGame(false);
		NewWeapon->SetOwner(GetOwner());
		NewWeapon->OnEquipped();
		if(bWantToShoot)
		{
			NewWeapon->StartShoot();
		}
		OnWeaponSwitched.Broadcast(NewWeapon,Slot);
	}
	currentSlotSelected = Slot;
}
