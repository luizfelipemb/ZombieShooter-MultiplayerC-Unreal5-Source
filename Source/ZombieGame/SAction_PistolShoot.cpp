// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_PistolShoot.h"

#include "SAttributesComponent.h"
#include "SCharacter.h"

void USAction_PistolShoot::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ASCharacter* MyOwner = Cast<ASCharacter>(Instigator);
	if (MyOwner)
	{
		// Setup the query to detect dynamic objects
        FCollisionObjectQueryParams ObjectQueryParams;
        ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

        // Get the owner's location and forward direction
        FVector OwnerLocation = MyOwner->GetActorLocation();
        FRotator OwnerRotation = MyOwner->GetActorRotation();

        // Calculate the end point by projecting forward from the owner's location
        FVector End = OwnerLocation + (OwnerRotation.Vector() * 1000); // Trace 1000 units forward

        TArray<FHitResult> Hits;
        float Radius = 30.0f;
        FCollisionShape Shape;
        Shape.SetSphere(Radius);

        // Setup the collision query to ignore the instigator
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(MyOwner);

        // Perform a sphere sweep from OwnerLocation to End
        bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, OwnerLocation, End, FQuat::Identity, ObjectQueryParams, Shape, QueryParams);

        // Set the color of the debug sphere based on whether a hit was detected
        FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
		if(bShowDebugInfo) {DrawDebugLine(GetWorld(), OwnerLocation, End, LineColor, false, 2.0f, 0, 2.0f);}
        // Loop through all hits and interact with the first valid object
        for (const FHitResult& Hit : Hits)
        {
            AActor* HitActor = Hit.GetActor();
            if (HitActor)
            {
                // Get the attributes component and apply health change
                USAttributesComponent* AttributesComp = Cast<USAttributesComponent>(HitActor->GetComponentByClass(USAttributesComponent::StaticClass()));
                if (AttributesComp)
                {
                    AttributesComp->ApplyHealthChange(MyOwner,-20.0f);
                	if(bShowDebugInfo) {DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);}
                	break;
                }
            }
        }
	}
}
