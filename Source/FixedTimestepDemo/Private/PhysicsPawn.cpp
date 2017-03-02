// Copyright 2017 0lento. All Rights Reserved.

#include "FixedTimestepDemo.h"
#include "PhysicsPublic.h"
#include "PhysicsPawn.h"


APhysicsPawn::APhysicsPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;
	PrimaryActorTick.bStartWithTickEnabled = true;

	PostPhysicsTickFunction.TickGroup = TG_PostPhysics;
	PostPhysicsTickFunction.bCanEverTick = true;
	PostPhysicsTickFunction.bStartWithTickEnabled = true;
}

void APhysicsPawn::BeginPlay()
{
	Super::BeginPlay();

	if (!IsTemplate() && PostPhysicsTickFunction.bCanEverTick)
	{
		PostPhysicsTickFunction.Target = this;
		PostPhysicsTickFunction.SetTickFunctionEnable(PostPhysicsTickFunction.bStartWithTickEnabled);
		PostPhysicsTickFunction.RegisterTickFunction(GetLevel());
	}

	FPhysScene* PScene = GetWorld()->GetPhysicsScene();
	if (PScene != NULL)
	{
		OnPhysScenePreTickHandle = PScene->OnPhysScenePreTick.AddUObject(this, &APhysicsPawn::PhysScenePreTick);
		OnPhysSceneStepHandle = PScene->OnPhysSceneStep.AddUObject(this, &APhysicsPawn::PhysSceneStep);
	}
}

void FPostPhysicsTickFunction::ExecuteTick(float DeltaTime,	ELevelTick TickType, ENamedThreads::Type CurrentThread,	const FGraphEventRef& CompletionGraphEvent)
{
	if (Target && !Target->HasAnyFlags(EObjectFlags::RF_BeginDestroyed | EObjectFlags::RF_FinishDestroyed))
	{
		FScopeCycleCounterUObject ActorScope(Target);
		Target->PostPhysicsTick(DeltaTime, TickType, *this);
	}
}

FString FPostPhysicsTickFunction::DiagnosticMessage()
{
	return Target->GetFullName() + TEXT("[FixedTimestepPawn Post Physics Tick]");
}

void APhysicsPawn::PhysScenePreTick(FPhysScene* PhysScene, uint32 SceneType, float DeltaTime)
{
	PhysicsStepCount = 0;
	PhysicsPreSim(DeltaTime);
}

void APhysicsPawn::PhysSceneStep(FPhysScene* PhysScene, uint32 SceneType, float DeltaTime)
{
	// If not the first physics step, make sure to run previous steps post step before new one
	if (PhysicsStepCount)
	{
		PhysicsPostStep(DeltaTime);
	}
	PhysicsStepCount++;
	PhysicsStep(DeltaTime);
}

void APhysicsPawn::PostPhysicsTick(float DeltaTime, ELevelTick TickType, FPostPhysicsTickFunction& TickFunction)
{
	PhysicsPostStep(DeltaTime); // Run PhysScenePostTick for the last physics step
	PhysicsPostSim(DeltaTime);
}

void APhysicsPawn::PhysicsPreSim(float DeltaTime)
{

}
void APhysicsPawn::PhysicsStep(float DeltaTime)
{

}
void APhysicsPawn::PhysicsPostStep(float DeltaTime)
{

}
void APhysicsPawn::PhysicsPostSim(float DeltaTime)
{

}
