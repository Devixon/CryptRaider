// Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.


#include "SwitchComponent.h"

// Sets default values for this component's properties
USwitchComponent::USwitchComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USwitchComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USwitchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

void USwitchComponent::DoSwitch(bool NewEnableSwitch)
{
	EnableSwitch = NewEnableSwitch;
	if (VisibleComponent)
	{
		VisibleVoid();
	}
	if (PlayComponent)
	{
		PlayVoid();
	}
}

void USwitchComponent::SetVisible(USceneComponent* NewVisibleComponent)
{
	VisibleComponent = NewVisibleComponent;
}

void USwitchComponent::VisibleVoid()
{
	VisibleComponent->SetVisibility(true);
}

void USwitchComponent::SetPlay(UActorComponent* NewPlayComponent)
{
	PlayComponent = NewPlayComponent;
}

void USwitchComponent::PlayVoid()
{
	
}
