// Copyright 2017 0lento. All Rights Reserved.

#include "FixedTimestepDemo.h"
#include "PhysicsPublic.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "PhysicsDataComponent.h"

UPhysicsDataComponent::UPhysicsDataComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPhysicsDataComponent::BeginPlay()
{
	Super::BeginPlay();
	FPhysScene* PScene = GetWorld()->GetPhysicsScene();
	if (PScene != NULL)
	{
		OnPhysSceneStepHandle = PScene->OnPhysSceneStep.AddUObject(this, &UPhysicsDataComponent::PhysSceneStep);
	}
}

void UPhysicsDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPhysicsDataComponent::PhysSceneStep(FPhysScene* PhysScene, uint32 SceneType, float DeltaTime)
{
	PhysicsTicks.Add(DeltaTime);
}

TArray<float> UPhysicsDataComponent::GetPhysicsTickData()
{
	TArray<float> Result(PhysicsTicks);
	PhysicsTicks.Empty(0);
	return Result;
}

int UPhysicsDataComponent::GetPhysicsMode()
{
	UPhysicsSettings* PhysSetting = UPhysicsSettings::Get();
	if (PhysSetting->bFixedTimestepSubsteps && PhysSetting->bSubstepping)
	{
		return 2;
	}
	else if (PhysSetting->bSubstepping)
	{
		return 1;
	}
	return 0;
}

void UPhysicsDataComponent::ReloadLevel(int PhysicsMode)
{
	if (PhysicsMode != GetPhysicsMode())
	{
		UPhysicsSettings* PhysSetting = UPhysicsSettings::Get();
		switch (PhysicsMode)
		{
			case 1:
				PhysSetting->bSubstepping = true;
				PhysSetting->bFixedTimestepSubsteps = false;
				break;
			case 2:
				PhysSetting->bSubstepping = true;
				PhysSetting->bFixedTimestepSubsteps = true;
				break;
			default:
				PhysSetting->bSubstepping = false;
				PhysSetting->bFixedTimestepSubsteps = false;
				break;
		}
	}
	UGameplayStatics::OpenLevel(GetWorld(), "TestMap");
}