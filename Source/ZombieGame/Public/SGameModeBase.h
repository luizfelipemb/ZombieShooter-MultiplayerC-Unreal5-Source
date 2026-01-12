// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class ASAICharacter;
class UEnvQuery;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewRoundStart,int32,NewRound);

UCLASS()
class ZOMBIEGAME_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly,Category="AI")
	TSubclassOf<ASAICharacter> MinionClass;
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly,Category="AI")
	UCurveFloat* SpawnBotCurve;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	int32 aliveZombies = 0;
	
	FTimerHandle TimerHandle_SpawnBots;
	UPROPERTY(EditDefaultsOnly,Category="AI")
	float SpawnTimerInterval;

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
	UFUNCTION()
	void SpawnBotTimerElapsed();
public:
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category = "Events")
	FOnNewRoundStart OnNewRoundStart;
	UFUNCTION()
    void OnZombieDied();
	ASGameModeBase() = default;
	virtual void StartPlay() override;
};
