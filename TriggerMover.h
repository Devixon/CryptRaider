//  Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.h"
#include "CheckerTriggersComponent.h"
#include "TriggerMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPT_RAIDER_API UTriggerMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);

	UFUNCTION(BlueprintCallable)
	void CanMove(bool EnableMover);

	UFUNCTION(BlueprintCallable)
	void SetCheckerTriggers(UCheckerTriggersComponent* CheckerTriggers);

	UFUNCTION(BlueprintCallable)
	void CanTrigger(bool EnableTrigger);

private:

	UPROPERTY(EditAnywhere)
	bool EnableMover;

	UPROPERTY(EditAnywhere)
	FName ActorTag;
	UPROPERTY(EditAnywhere)
	bool EnableTrigger = false;

	UMover* Mover;
	UCheckerTriggersComponent* CheckerTriggers;

};
