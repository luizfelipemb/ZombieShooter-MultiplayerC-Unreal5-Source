// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"
#include "EngineUtils.h"
#include "SXpAttribute.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "../SAttributesComponent.h"

class ASAICharacter;

static TAutoConsoleVariable<bool> CVarDebugZombieSpawn(
	TEXT("su.ZombieSpawnDebugger"),false,TEXT("Enable Debug messages for Zombie Spawns."),ECVF_Cheat);

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	SpawnBotTimerElapsed();
	//GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots,this, &ASGameModeBase::SpawnBotTimerElapsed,SpawnTimerInterval,false);
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(
		this,SpawnBotQuery,this,EEnvQueryRunMode::AllMatching,nullptr);
	if(ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this,&ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnZombieDied()
{
	aliveZombies--;
	SpawnBotTimerElapsed();
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                      EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed!"));
		return;
	}
	
	int BotsToSpawn = 0;
	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	USXpAttribute* xpComp = Cast<USXpAttribute>(playerPawn->GetComponentByClass(USXpAttribute::StaticClass()));
	int PlayerLevel = xpComp->GetLevel();
	if(SpawnBotCurve)
	{
		PlayerLevel++;
		BotsToSpawn = SpawnBotCurve->GetFloatValue(PlayerLevel) - aliveZombies;
		OnNewRoundStart.Broadcast(PlayerLevel);
	}
	
	TArray<FVector> Locations;
	QueryInstance->GetQueryResultsAsLocations(Locations);
	
	if(CVarDebugZombieSpawn.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bots to spawn: %d"), BotsToSpawn);
		UE_LOG(LogTemp, Warning, TEXT("Found %d locations"), (int)Locations.Num());
	}
	
	if (!MinionClass)
	{
		UE_LOG(LogTemp, Error, TEXT("MinionClass is not set!"));
		return;
	}
	for(int i = 0; i < BotsToSpawn; i++)
	{
		if(Locations.IsValidIndex(i))
		{
			ASAICharacter* SpawnedZombie = GetWorld()->SpawnActor<ASAICharacter>(MinionClass,Locations[i],FRotator::ZeroRotator);
			if (SpawnedZombie)
			{
				SpawnedZombie->OnDeath.AddDynamic(this,&ASGameModeBase::OnZombieDied);
                aliveZombies++;
			}
		}
	}
}
