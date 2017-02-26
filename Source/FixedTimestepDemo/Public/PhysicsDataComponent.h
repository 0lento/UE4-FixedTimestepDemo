// Copyright 2017 0lento. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "PhysicsDataComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIXEDTIMESTEPDEMO_API UPhysicsDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPhysicsDataComponent();

protected:
	virtual void BeginPlay() override;

private:
	FDelegateHandle OnPhysSceneStepHandle;
	void PhysSceneStep(FPhysScene* PhysScene, uint32 SceneType, float DeltaTime);
	UPROPERTY()
	TArray<float> PhysicsTicks;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Physics")
	TArray<float> GetPhysicsTickData();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Physics")
	int GetPhysicsMode();
	UFUNCTION(BlueprintCallable, Category = "Physics")
	void ReloadLevel(int PhysicsMode);
};
