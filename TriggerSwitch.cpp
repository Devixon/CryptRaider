// Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.


#include "TriggerSwitch.h"

// Sets default values for this component's properties
UTriggerSwitch::UTriggerSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTriggerSwitch::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// UE_LOG(LogTemp, Display, TEXT("Test"));
}


// Called every frame
void UTriggerSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTriggerSwitch::SetSwitch(USwitchComponent* NewSwitch)
{
	Switch.AddUnique(NewSwitch);
}

void UTriggerSwitch::CanSwitch(bool NewEnableSwitch)
{
	EnableSwitch = NewEnableSwitch;
	DoIt();
}

void UTriggerSwitch::DoIt()
{
	if (Switch.Num() > 0)
	{
		if (EnableSwitch)
		{
			for (int32 i = 0; i < Switch.Num(); i++)
			{
				Switch[i]->DoSwitch(true);
			}
		}
	}
}

