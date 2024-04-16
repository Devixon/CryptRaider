//  Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.


#include "TriggerBoxComponent.h"

UTriggerBoxComponent::UTriggerBoxComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTriggerBoxComponent::BeginPlay()
{
	Super::BeginPlay();

	Box = UTriggerBoxComponent::BoxExtent;

	PlacementLocationForItemOffsetDefault = PlacementLocationOffset;

	if (CompatibleActorTag == "None")
	{
		CompatibleActorTag = AcceptableActorTag;
	}

	// UE_LOG(LogTemp, Display, TEXT("Test"));

}

void UTriggerBoxComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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
		FVector BigBox = FVector(30, 30, 30) + Box;
		UTriggerBoxComponent::SetBoxExtent(BigBox);
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false);
		}
		SetPlacement(Actor, DeltaTime);
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		CompatibleActor = Actor->ActorHasTag(CompatibleActorTag);
		StringCompatibleActorTag = CompatibleActorTag.ToString() + NumberTag;
		ActorForItemOff = Actor->ActorHasTag(NamePlacementLocationForItemOffset);

		if (ActorForItemOff)
		{
			PlacementLocationOffset = PlacementLocationForItemOffset;
		}
		else
		{
			PlacementLocationOffset = PlacementLocationForItemOffsetDefault;
		}

		if (Mover != nullptr)
		{
			Mover->SetShouldMove(true);
			if (BothTarget)
			{
				CheckerTriggers->GoMover(true);
				CheckerTriggers->AddArray(StringCompatibleActorTag);
			}
		}
		else if (CompatibleActor)
		{
			CheckerTriggers->GoMover(true);
			CheckerTriggers->AddArray(StringCompatibleActorTag);

		}

	}
	else
	{
		if (Mover != nullptr)
		{
			Mover->SetShouldMove(false);
			if (BothTarget)
			{
				CheckerTriggers->GoMover(false);
				CheckerTriggers->DeleteArray(StringCompatibleActorTag);
			}
		}
		else if (CompatibleActor)
		{
			CheckerTriggers->GoMover(false);
			CheckerTriggers->DeleteArray(StringCompatibleActorTag);
		}
		OriginalPlacement = true;
		UTriggerBoxComponent::SetBoxExtent(Box);
	}

}

void UTriggerBoxComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UTriggerBoxComponent::SetCheckerTriggers(UCheckerTriggersComponent* NewCheckerTriggers)
{
	CheckerTriggers = NewCheckerTriggers;
}

void UTriggerBoxComponent::SetPlacement(AActor* Actor, float DeltaTime)
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

AActor* UTriggerBoxComponent::GetAcceptableActor() const
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
