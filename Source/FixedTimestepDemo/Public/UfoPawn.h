// Copyright 2017 0lento. All Rights Reserved.

#pragma once

#include "PhysicsPawn.h"
#include "UfoPawn.generated.h"

class USuspensionComponent;

UCLASS()
class FIXEDTIMESTEPDEMO_API AUfoPawn : public APhysicsPawn
{
	GENERATED_BODY()
	
public:
	AUfoPawn();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual void PhysicsPreSim(float DeltaTime) override;
	virtual void PhysicsStep(float DeltaTime) override;
	virtual void PhysicsPostStep(float DeltaTime) override;
	virtual void PhysicsPostSim(float DeltaTime) override;

	UPROPERTY()
	TArray<USuspensionComponent*> Thrusters;

public:
	
	UPROPERTY(EditAnywhere, Category = "Main Body")
	UStaticMeshComponent* RootMesh;
	UPROPERTY(EditAnywhere, Category = "Main Body")
	UStaticMeshComponent* ExtraMesh;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int ThrusterAmount = 12;
	UPROPERTY(EditAnywhere, Category = "Setup")
	float ThrusterDistanceFromCenter = 100.f;
	UPROPERTY(EditAnywhere, Category = "Setup")
	float SuspensionLength = 150.f;
	UPROPERTY(EditAnywhere, Category = "Setup")
	float SpringCoeff = 250.0;
	UPROPERTY(EditAnywhere, Category = "Setup")
	float DamperCoeff = 50.f;
	
};
