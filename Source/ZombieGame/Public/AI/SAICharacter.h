// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombieGame/SAttributesComponent.h"
#include "SAICharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class ZOMBIEGAME_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASAICharacter();

protected:
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributesComponent* OwningComp, float NewHealth, float Delta,float MaxHealth);
	virtual void PostInitializeComponents() override;
	
	UPROPERTY(VisibleAnywhere)
	USAttributesComponent* AttributesComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsDead = false;
public:
	UPROPERTY(VisibleAnywhere,BlueprintAssignable)
	FOnDeath OnDeath;
};
