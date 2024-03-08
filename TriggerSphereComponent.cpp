//  Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.


#include "TriggerSphereComponent.h"

UTriggerSphereComponent::UTriggerSphereComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTriggerSphereComponent::BeginPlay()
{
	Super::BeginPlay();

	Sphere = UTriggerSphereComponent::SphereRadius;
	
	if (CompatibleActorTag == "None")
	{
		CompatibleActorTag = AcceptableActorTag;
	}

	// UE_LOG(LogTemp, Display, TEXT("Test"));

}

void UTriggerSphereComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CheckerTriggers == nullptr)
	{
		if (Mover == nullptr)
		{
			return;
		}
	}

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		UTriggerSphereComponent::SetSphereRadius(Sphere+30);

		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		SetPlacement(Actor, DeltaTime);
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		CompatibleActor = Actor->ActorHasTag(CompatibleActorTag);
		if (Mover != nullptr)
		{
			Mover->SetShouldMove(true);
		}
		else if (CompatibleActor)
		{
			CheckerTriggers->GoMover(true);
			CheckerTriggers->AddArray(CompatibleActorTag);

		}

	}
	else
	{
		if (Mover != nullptr)
		{
			Mover->SetShouldMove(false);
		}
		else if (CompatibleActor)
		{
			CheckerTriggers->GoMover(false);
			CheckerTriggers->DeleteArray(CompatibleActorTag);
		}
		OriginalPlacement = true;
		UTriggerSphereComponent::SetSphereRadius(Sphere);
	}

}

void UTriggerSphereComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UTriggerSphereComponent::SetCheckerTriggers(UCheckerTriggersComponent* NewCheckerTriggers)
{
	CheckerTriggers = NewCheckerTriggers;
}

void UTriggerSphereComponent::SetPlacement(AActor* Actor, float DeltaTime)
{
	if (OriginalPlacement)
	{
		OriginalPlacementLocation = Actor->GetActorLocation();
		OriginalPlacementCorner = Actor->GetActorRotation();
		OriginalPlacementCornerVector = FVector(OriginalPlacementCorner.Pitch, OriginalPlacementCorner.Yaw, OriginalPlacementCorner.Roll);

		OriginalPlacement = false;
	}

	PlacementLocation = GetComponentLocation();
	PlacementCorner = GetComponentRotation();
	FVector PlacementCornerVector = FVector(PlacementCorner.Pitch, PlacementCorner.Yaw, PlacementCorner.Roll);


	FVector CurrnetPlacementLocation = Actor->GetActorLocation();
	FVector TargetPlacementLocation = PlacementLocation + PlacementLocationOffset;
	float Speed = FVector::Distance(OriginalPlacementLocation, TargetPlacementLocation) / PlacementingTime;

	FVector NewPlacementLocation = FMath::VInterpConstantTo(CurrnetPlacementLocation, TargetPlacementLocation, DeltaTime, Speed);

	//Probobly can do better
	FRotator CurrnetPlacementCorner = Actor->GetActorRotation();
	FVector CurrnetPlacementCornerVector = FVector(CurrnetPlacementCorner.Pitch, CurrnetPlacementCorner.Yaw, CurrnetPlacementCorner.Roll);
	FVector PlacementCornerOffsetVector = FVector(PlacementCornerOffset.Pitch, PlacementCornerOffset.Yaw, PlacementCornerOffset.Roll);
	FVector TargetPlacementCorner = PlacementCornerVector + PlacementCornerOffsetVector;
	float SpeedCorner = FVector::Distance(OriginalPlacementCornerVector, TargetPlacementCorner) / PlacementingTime;

	FVector NewPlacementCornerVector = FMath::VInterpConstantTo(CurrnetPlacementCornerVector, TargetPlacementCorner, DeltaTime, SpeedCorner);
	FRotator NewPlacementCorner = FRotator(NewPlacementCornerVector.X, NewPlacementCornerVector.Y, NewPlacementCornerVector.Z);

	Actor->SetActorLocationAndRotation(NewPlacementLocation, NewPlacementCorner);

}

AActor* UTriggerSphereComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (AActor* Actor : Actors)
	{
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if (HasAcceptableTag && !IsGrabbed)
		{
			return Actor;
		}
	}

	return nullptr;
}
