// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SXpAttribute.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnXPChanged,USXpAttribute*,OwningComp,
																float,NewXp,float, MaxXp, float,Delta,
																int, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChanged,int, Level);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIEGAME_API USXpAttribute : public UActorComponent
{
	GENERATED_BODY()

public:	
	USXpAttribute();
	void AddXp(float Amount);
	
	UFUNCTION(BlueprintCallable, Category = "XP")
	float GetMaxXpParam() const { return XpToNextLevel; }
	
	UFUNCTION(BlueprintCallable, Category = "XP")
	int GetLevel() const { return Level; }
	
	UPROPERTY(BlueprintAssignable)
	FOnXPChanged OnXPChanged;
	UPROPERTY(BlueprintAssignable)
	FOnLevelChanged OnLevelChanged;
protected:
	virtual void BeginPlay() override;
	
	float Xp;
	float XpToNextLevel;
	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* XpCurve;
	int Level;
};
