// Copyright 2017 0lento. All Rights Reserved.

#include "FixedTimestepDemo.h"
#include "SuspensionComponent.h"
#include "UfoPawn.h"

AUfoPawn::AUfoPawn()
{
	// you can override regular Tick settings here
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics; // doesn't need to be PrePhysics
	PrimaryActorTick.bStartWithTickEnabled = true;

	// you can disable PostPhysicsTick here
	PostPhysicsTickFunction.bCanEverTick = true;
	PostPhysicsTickFunction.bStartWithTickEnabled = true;

	// setup the UFO meshes and thrusters
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body"));
	ExtraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Detail"));


	RootMesh->SetWorldScale3D(FVector(2.f, 2.f, 0.2f));
	ExtraMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 1.5f));
	ExtraMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.0f));

	// create thrusters in a circle around the UFO
	for (int i = 0; i < ThrusterAmount; i++)
	{
		USuspensionComponent* SuspensionElement = CreateDefaultSubobject<USuspensionComponent>(FName(*FString::Printf(TEXT("Suspension%d"), i)));
		SuspensionElement->SetupAttachment(RootMesh);
		const float AngleRad = (2.f * PI) * ((float)i / (float)ThrusterAmount);
		const float x = ThrusterDistanceFromCenter * FMath::Cos(AngleRad);
		const float y = ThrusterDistanceFromCenter * FMath::Sin(AngleRad);
		SuspensionElement->SetRelativeLocation(FVector(x, y, 0.0f));
		Thrusters.Add(SuspensionElement);
	}

	SetRootComponent(RootMesh);
	ExtraMesh->SetupAttachment(RootMesh);

	RootMesh->SetSimulatePhysics(true);
	ExtraMesh->SetSimulatePhysics(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/Meshes/SM_Sphere.SM_Sphere'"));
	RootMesh->SetStaticMesh(SM.Object);
	ExtraMesh->SetStaticMesh(SM.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> MI(TEXT("MaterialInstanceConstant'/Game/Materials/MI_Black.MI_Black'"));
	ExtraMesh->SetMaterial(0, MI.Object);
}

void AUfoPawn::BeginPlay()
{
	Super::BeginPlay();

	for (USuspensionComponent* Thruster : Thrusters)
	{
		Thruster->SuspensionLength = SuspensionLength;
		Thruster->SpringCoeff = SpringCoeff;
		Thruster->DamperCoeff = DamperCoeff;
	}
}

void AUfoPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Executed before physics steps
void AUfoPawn::PhysicsPreSim(float DeltaTime)
{
}

// Executed on individual physics step
void AUfoPawn::PhysicsStep(float DeltaTime)
{

	for (USuspensionComponent* Thruster : Thrusters)
	{
		Thruster->Update(DeltaTime);
	}
}

// Executed after individual physics step
void AUfoPawn::PhysicsPostStep(float DeltaTime)
{
}

// Executed after physics steps
void AUfoPawn::PhysicsPostSim(float DeltaTime)
{
}
