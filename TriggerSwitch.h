// Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SwitchComponent.h"
#include "TriggerSwitch.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPT_RAIDER_API UTriggerSwitch : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTriggerSwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetSwitch(USwitchComponent* Switch);

	UFUNCTION(BlueprintCallable)
	void CanSwitch(bool EnableSwitch);

private:

	void DoIt();

	UPROPERTY(EditAnywhere)
	bool EnableSwitch;

	TArray<USwitchComponent*> Switch;
		
};
