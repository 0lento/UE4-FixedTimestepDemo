// Copyright 2017 0lento. All Rights Reserved.

#pragma once

#include "Components/SceneComponent.h"
#include "SuspensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIXEDTIMESTEPDEMO_API USuspensionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	USuspensionComponent();

protected:
	FBodyInstance* BodyInstance;
	UPROPERTY()
	float PreviousDistance;

public:
	virtual void BeginPlay() override;
	FHitResult Trace(FVector TraceStart, FVector TraceEnd);
	void Update(float PhysicsDeltaTime);

	UPROPERTY()
	float SuspensionLength;
	UPROPERTY()
	float SpringCoeff;
	UPROPERTY()
	float DamperCoeff;

};
