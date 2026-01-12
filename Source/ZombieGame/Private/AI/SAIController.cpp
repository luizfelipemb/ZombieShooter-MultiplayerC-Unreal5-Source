// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieGame/SAttributesComponent.h"

class USAttributesComponent;

void ASAIController::ApplyAttack() const
{
	APawn* player = UGameplayStatics::GetPlayerPawn(this,0);
	USAttributesComponent* AttributesComp = Cast<USAttributesComponent>(
			player->GetComponentByClass(USAttributesComponent::StaticClass()));
	if (ensure(AttributesComp))
	{
		AttributesComp->ApplyHealthChange(Owner,-20.0f);
	}
}

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this,0);
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation",MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor",MyPawn);
	}
}
