//  Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.


#include "TriggerMover.h"

// Sets default values for this component's properties
UTriggerMover::UTriggerMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerMover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTriggerMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CheckerTriggers == nullptr)
	{
		if (Mover == nullptr)
		{
			return;
		}
	}

	if (Mover != nullptr)
	{
		if (EnableMover)
		{
			Mover->SetShouldMove(true);
		}
		else
		{
			Mover->SetShouldMove(false);
		}
	}
	else
	{
		if (EnableTrigger)
		{
			CheckerTriggers->GoMover(true);
			CheckerTriggers->AddArray(ActorTag);
		}
		else
		{
			CheckerTriggers->GoMover(false);
			CheckerTriggers->DeleteArray(ActorTag);
		}
	}
}

void UTriggerMover::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UTriggerMover::CanMove(bool NewEnableMover)
{
	EnableMover = NewEnableMover;
}

void UTriggerMover::SetCheckerTriggers(UCheckerTriggersComponent* NewCheckerTriggers)
{
	CheckerTriggers = NewCheckerTriggers;
}

void UTriggerMover::CanTrigger(bool NewEnableTrigger)
{
	EnableTrigger = NewEnableTrigger;
}

