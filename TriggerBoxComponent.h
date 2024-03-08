//  Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "CheckerTriggersComponent.h"
#include "TriggerBoxComponent.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPT_RAIDER_API UTriggerBoxComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTriggerBoxComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);

	UFUNCTION(BlueprintCallable)
	void SetCheckerTriggers(UCheckerTriggersComponent* CheckerTriggers);

private:

	UPROPERTY(EditAnywhere)
	FName AcceptableActorTag;

	UPROPERTY(EditAnywhere)
	FName CompatibleActorTag;
	bool CompatibleActor = false;

	FVector PlacementLocation;
	FRotator PlacementCorner;

	UPROPERTY(EditAnywhere, Category = "Placement Point")
	FVector PlacementLocationOffset;
	UPROPERTY(EditAnywhere, Category = "Placement Point")
	FRotator PlacementCornerOffset;

	UPROPERTY(EditAnywhere, Category = "Placement Point")
	float PlacementingTime = 1;

	bool OriginalPlacement = true;
	FVector OriginalPlacementLocation;
	FRotator OriginalPlacementCorner;
	FVector OriginalPlacementCornerVector;

	FVector Box;

	void SetPlacement(AActor* Actor, float DeltaTime);

	UMover* Mover;
	UCheckerTriggersComponent* CheckerTriggers;

	AActor* GetAcceptableActor() const;

};
