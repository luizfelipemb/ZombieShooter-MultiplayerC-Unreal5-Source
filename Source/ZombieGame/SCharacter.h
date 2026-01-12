// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributesComponent.h"
#include "SInteractionComponent.h"
#include "SUpgradesManager.h"
#include "SWeaponsManager.h"
#include "SXpAttribute.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USActionComponent;
class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;
class ASWeapon;


UCLASS()
class ZOMBIEGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ASCharacter();
protected:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USAttributesComponent* AttributeComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USXpAttribute* XpAttributeComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USUpgradesManager* UpgradesManagerComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USWeaponsManager* WeaponsManagerComp;
	UPROPERTY(VisibleAnywhere)
    USInteractionComponent* InteractionComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components")
    USActionComponent* ActionComp;

	void SelectWeapon1() { WeaponsManagerComp->SwitchWeapon(0); }
	void SelectWeapon2() { WeaponsManagerComp->SwitchWeapon(1); }
	void SelectWeapon3() { WeaponsManagerComp->SwitchWeapon(2); }
	void SelectWeapon4() { WeaponsManagerComp->SwitchWeapon(3); }
	void Reload() { WeaponsManagerComp->ReloadButtonPressed();}
	void HackXP();
	
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryAttack();
	void PrimaryInteract();
public:	
	virtual void Tick(float DeltaTime) override;
	void PrimaryAttackRelease();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
