//  Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPT_RAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool ShouldMove);

	UFUNCTION(BlueprintCallable)
	void SetCover(UPrimitiveComponent* Cover);

private:
	UPROPERTY(EditAnywhere, Category = "Mover")
	FVector	MoveOffset;

	UPROPERTY(EditAnywhere, Category = "Move Cover")
	FVector	CoverMoveOffset;

	UPROPERTY(EditAnywhere, Category = "Mover")
	float MoveTime = 5;

	UPROPERTY(EditAnywhere, Category = "Move Cover")
	float CoverMoveTime = 1;

	bool ShouldMove = false;
	bool ShouldCoverMove = false;
	bool CoverMoveDone = false;

	FVector OriginalLocation;
	FVector OriginalCoverLocation;

	UPrimitiveComponent* Cover;
		
};
