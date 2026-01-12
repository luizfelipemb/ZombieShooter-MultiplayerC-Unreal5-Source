// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"

#include "ZombieGame/SAttributesComponent.h"


ASWeapon::ASWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(Mesh);
	
	CollisionDetectionMesh = CreateDefaultSubobject<UStaticMeshComponent>("CollisionMesh");
	CollisionDetectionMesh->SetupAttachment(Mesh);
	CollisionDetectionMesh->SetGenerateOverlapEvents(true);
	CollisionDetectionMesh->SetCollisionResponseToChannels(ECR_Overlap);
	CollisionDetectionMesh->CastShadow = false;
	CollisionDetectionMesh->OnComponentBeginOverlap.AddDynamic(this, &ASWeapon::OnCollisionMeshBeginOverlap);
	CollisionDetectionMesh->OnComponentEndOverlap.AddDynamic(this, &ASWeapon::OnCollisionMeshEndOverlap);
	UpgradesManager=CreateDefaultSubobject<USWeaponUpgradesManager>("UpgradesManager");
}

void ASWeapon::ApplyRangeMultiplier(FVector Multiplier)
{
	CollisionDetectionMesh->SetRelativeScale3D(CollisionDetectionMesh->GetComponentScale() * Multiplier);
}

void ASWeapon::OnEquipped()
{
	bCanShoot = false;
	bShooting = false;
	bReadyToShoot = false;
	GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &ASWeapon::ResetShootCooldown, WeaponAntiSpamCooldown,
	                                false);
	OnWeaponUpdateAmmo.Broadcast(AmmoInWeapon,AmmoInPockets);
}

void ASWeapon::StartReload()
{
	if (AmmoInPockets <= 0)
	{
		StopShoot();
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Coudnt Reload"));
		return;
	}
	OnWeaponReloadStart.Broadcast(WeaponType,AmmoInWeapon,AmmoInPockets,ReloadRate);
}

void ASWeapon::CompleteReload()
{
	int AmmoToBePut = AmmoMaxCapacity - AmmoInWeapon;
	if (AmmoToBePut < AmmoInPockets)
	{
		AmmoInPockets -= AmmoToBePut;
		AmmoInWeapon = AmmoMaxCapacity;
	}
	else
	{
		AmmoInWeapon += AmmoInPockets;
		AmmoInPockets = 0;
	}
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Reloaded Complete"));
	OnWeaponReloadFinished.Broadcast(WeaponType,AmmoInWeapon,AmmoInPockets,ReloadRate);
}

void ASWeapon::ResetShootCooldown()
{
	bCanShoot = true;
	if (bReadyToShoot)
	{
		if (AmmoInWeapon > 0)
		{
			OnWeaponShoot.Broadcast(WeaponType, FireRate,AmmoInWeapon);
			bShooting = true;
		}
	}
}

void ASWeapon::StartShoot()
{
	bReadyToShoot = true;
	if (bCanShoot)
	{
		if (AmmoInWeapon > 0)
		{
			OnWeaponShoot.Broadcast(WeaponType, FireRate,AmmoInWeapon);
			bShooting = true;
		}
		else
		{
			bReadyToShoot = false;
		}
	}
}

void ASWeapon::StopShoot()
{
	bReadyToShoot = false;
	if (bCanShoot && bShooting)
	{
		bCanShoot = false;
		bShooting = false;
		OnWeaponStopShoot.Broadcast();
		GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &ASWeapon::ResetShootCooldown,
		                                WeaponAntiSpamCooldown, false);
	}
}

void ASWeapon::FindClosestTarget()
{
	AActor* ClosestActor = nullptr;
	CurrentTarget = nullptr;

	float ClosestDistanceSq = FLT_MAX;
	FVector WeaponLocation = GetActorLocation();

	for (AActor* TargetActor : TargetActors)
	{
		if (TargetActor)
		{
			float DistanceSq = FVector::DistSquared(WeaponLocation, TargetActor->GetActorLocation());
			if (DistanceSq < ClosestDistanceSq)
			{
				ClosestDistanceSq = DistanceSq;
				ClosestActor = TargetActor;
			}
		}
	}
	if (ClosestActor && ClosestActor != GetOwner())
	{
		CurrentTarget = ClosestActor;
	}
}

void ASWeapon::ApplyDamageToTarget()
{
	if (bShooting && bCanShoot && AmmoInWeapon>0)
	{
		FindClosestTarget();
		if (CurrentTarget)
		{
			UActorComponent* Comp = CurrentTarget->GetComponentByClass(USAttributesComponent::StaticClass());
			if (Comp)
			{
				Cast<USAttributesComponent>(Comp)->ApplyHealthChange(GetOwner(),WeaponDamage);
			}
		}
		ShootEffect(CurrentTarget);
		AmmoInWeapon--;
		OnWeaponUpdateAmmo.Broadcast(AmmoInWeapon,AmmoInPockets);
		if (AmmoInWeapon <= 0)
		{
			StartReload();
		}
	}
}

void ASWeapon::ShootEffect_Implementation(AActor* targetActor)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Shoot Effect Base"));
}

void ASWeapon::OnCollisionMeshBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                           const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		if (USAttributesComponent* AttributesComp = OtherActor->FindComponentByClass<USAttributesComponent>())
		{
			TargetActors.AddUnique(OtherActor); // Add actor only if it's not already in the list
			UE_LOG(LogTemp, Warning, TEXT("Collision Detected with: %s"), *OtherActor->GetName());
		}
	}
}

void ASWeapon::OnCollisionMeshEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		TargetActors.Remove(OtherActor);
	}
}
