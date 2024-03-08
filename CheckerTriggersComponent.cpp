//  Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.


#include "CheckerTriggersComponent.h"

// Sets default values for this component's properties
UCheckerTriggersComponent::UCheckerTriggersComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCheckerTriggersComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCheckerTriggersComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Mover == nullptr)
	{
		return;
	}
	
	if(MoverMustGo)
	{
		Mover->SetShouldMove(true);
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UCheckerTriggersComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UCheckerTriggersComponent::GoMover(bool NewMoverMustGo)
{
	if (Checker.Num() == HowMuchTriggers)
	{
		MoverMustGo = NewMoverMustGo;
	}
}

void UCheckerTriggersComponent::AddArray(FName New)
{
	Checker.AddUnique(New);
	for (int32 i = 0; i < Checker.Num(); i++)
	{
		float test = Checker.Num();
	}
}

void UCheckerTriggersComponent::DeleteArray(FName Delete)
{
	for (int32 i = 0; i < Checker.Num(); i++)
	{
		if (Checker[i] == Delete)
		{
			Checker.RemoveAt(i);
		}
	}
}
