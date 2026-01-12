
#include "SWallWeapon.h"

#include "ZombieGame/SCharacter.h"

ASWallWeapon::ASWallWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

void ASWallWeapon::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);
	UE_LOG(LogTemp,Warning,TEXT("Interacted with Wall Weapon"));
	
	UActorComponent* CompBeforeCast = InstigatorPawn->GetComponentByClass(USWeaponsManager::StaticClass());
	if(USWeaponsManager* WeaponsManager = Cast<USWeaponsManager>(CompBeforeCast))
	{
		WeaponsManager->EquipNewWeapon(WeaponToGive);
	}
}

void ASWallWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

