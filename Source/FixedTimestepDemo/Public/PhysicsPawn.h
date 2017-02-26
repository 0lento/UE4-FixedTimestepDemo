// Copyright 2017 0lento. All Rights Reserved.

#pragma once

#include "GameFramework/Pawn.h"
#include "PhysicsPawn.generated.h"

USTRUCT()
struct FPostPhysicsTickFunction : public FTickFunction
{
	GENERATED_BODY()

	class APhysicsPawn* Target;

	virtual void ExecuteTick(float DeltaTime, ELevelTick TickType, ENamedThreads::Type CurrentThread, const FGraphEventRef& CompletionGraphEvent) override;
	virtual FString DiagnosticMessage() override;
};

template<>
struct TStructOpsTypeTraits<FPostPhysicsTickFunction> : public TStructOpsTypeTraitsBase
{
	enum
	{
		WithCopy = false
	};
};


UCLASS()
class FIXEDTIMESTEPDEMO_API APhysicsPawn : public APawn
{
	GENERATED_BODY()

public:
	APhysicsPawn();
	void PostPhysicsTick(float DeltaTime, ELevelTick TickType, FPostPhysicsTickFunction& TickFunction);
	uint32 FORCEINLINE APhysicsPawn::GetPhysicsStepCount() { return PhysicsStepCount; }

private:
	FDelegateHandle OnPhysScenePreTickHandle;
	FDelegateHandle OnPhysSceneStepHandle;
	void PhysScenePreTick(FPhysScene* PhysScene, uint32 SceneType, float DeltaTime);
	void PhysSceneStep(FPhysScene* PhysScene, uint32 SceneType, float DeltaTime);

	UPROPERTY()
	uint32 PhysicsStepCount;

protected:
	FPostPhysicsTickFunction PostPhysicsTickFunction;

	virtual void BeginPlay() override;

	virtual void PhysicsPreSim(float DeltaTime);
	virtual void PhysicsStep(float DeltaTime);
	virtual void PhysicsPostStep(float DeltaTime);
	virtual void PhysicsPostSim(float DeltaTime);
};
