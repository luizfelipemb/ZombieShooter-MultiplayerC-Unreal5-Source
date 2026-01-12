// Fill out your copyright notice in the Description page of Project Settings.


#include "Upgrades/MovementSpeedUpgrade.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "ZombieGame/SCharacter.h"


void UMovementSpeedUpgrade::ApplyUpgrade(AActor* TargetActor, float EffectValue)
{
	if (!TargetActor) return;

	ASCharacter* TargetCharacter = Cast<ASCharacter>(TargetActor);
	if (TargetCharacter)
	{
		UCharacterMovementComponent* MovementComponent = TargetCharacter->GetCharacterMovement();
		if (MovementComponent)
		{
			float NewSpeed = MovementComponent->MaxWalkSpeed + EffectValue;
			MovementComponent->MaxWalkSpeed = NewSpeed;

			UE_LOG(LogTemp, Log, TEXT("Applying Movement Speed Upgrade: +%f. New Speed: %f"), EffectValue, NewSpeed);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to apply Movement Speed Upgrade: MovementComponent is null!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to apply Movement Speed Upgrade: TargetActor is not a Character!"));
	}
}
