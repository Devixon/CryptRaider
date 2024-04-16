//  Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Cover != nullptr)
	{
		if (ShouldCoverMove)
		{
			FVector TargetCoverLocation = OriginalCoverLocation + CoverMoveOffset;
			FVector CurrnetCoverLocation = Cover->GetRelativeLocation();
			float Speed = CoverMoveOffset.Length() / MoveTime;

			FVector NewCoverLocation = FMath::VInterpConstantTo(CurrnetCoverLocation, TargetCoverLocation, DeltaTime, Speed);
			Cover->SetRelativeLocation(NewCoverLocation);

			if (NewCoverLocation == TargetCoverLocation)
			{
				CoverMoveDone = true;
				ShouldMovePublic = CoverMoveDone;
			}
		}
		else
		{
			FVector CurrnetCoverLocation = Cover->GetRelativeLocation();
			float Speed = CoverMoveOffset.Length() / MoveTime;

			FVector NewCoverLocation = FMath::VInterpConstantTo(CurrnetCoverLocation, OriginalCoverLocation, DeltaTime, Speed);
			Cover->SetRelativeLocation(NewCoverLocation);

			CoverMoveDone = false;

		}
	}
	else
	{
		if (CoverMoveDone != true)
		{
			CoverMoveDone = true;
		}
	}

	if (ShouldMove && CoverMoveDone)
	{
		FVector TargetLocation = OriginalLocation + MoveOffset;
		FVector CurrnetLocation = GetOwner()->GetActorLocation();
		float Speed = MoveOffset.Length() / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrnetLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);

		CloseMovePublic = false;

	}
	else
	{
		FVector BackCurrnetLocation = GetOwner()->GetActorLocation();
		float Speed = MoveOffset.Length() / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(BackCurrnetLocation, OriginalLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);

		CloseMovePublic = true;
	}
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
	ShouldCoverMove = NewShouldMove;
	ShouldCoverMovePublic = NewShouldMove;
}

void UMover::SetCover(UPrimitiveComponent* NewCover)
{
	Cover = NewCover;
	OriginalCoverLocation = Cover->GetRelativeLocation();
}

