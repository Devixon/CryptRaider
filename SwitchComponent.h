// Copyright (C) 2024 Devixon This program comes with ABSOLUTELY NO WARRANTY and this is free software, and you are welcome to redistribute it under certain conditions open file "License.txt" for details.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SwitchComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPT_RAIDER_API USwitchComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USwitchComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void DoSwitch(bool EnableSwitch);

	UFUNCTION(BlueprintCallable)
	void SetVisible(USceneComponent* VisibleComponent);

	UFUNCTION(BlueprintCallable)
	void SetPlay(UActorComponent* PlayComponent);

private:

	void VisibleVoid();
	void PlayVoid();

	UPROPERTY(EditAnywhere)
	bool EnableSwitch;

	USceneComponent* VisibleComponent;

	UActorComponent* PlayComponent;
	
};
