// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDraw"),false,TEXT("Enable Debug Lines for Interact Component."),ECVF_Cheat);
// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();
	
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	// Get the owner's location and forward direction
	FVector OwnerLocation = MyOwner->GetActorLocation();
	FRotator OwnerRotation = MyOwner->GetActorRotation();

	// Calculate the end point by projecting forward from the owner's location
	FVector End = OwnerLocation + (OwnerRotation.Vector() * TraceDistance); // Trace 1000 units forward

	TArray<FHitResult> Hits;
	float Radius = 30.0f;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);

	// Perform a sphere sweep from OwnerLocation to End
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, OwnerLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	// Loop through all hits and interact with the first valid object
	for (FHitResult Hit : Hits)
	{
		if(bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2);
		}
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			// Check if the hit actor implements the gameplay interface
			if (HitActor->Implements<USGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				ISGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break; // Only interact with the first valid actor
			}
		}
	}
	if(bDebugDraw)
	{
		DrawDebugLine(GetWorld(), OwnerLocation, End, LineColor, false, 2, 0, 2);
	}
}


