// Copyright 2017 0lento. All Rights Reserved.

#include "FixedTimestepDemo.h"
#include "SuspensionComponent.h"


USuspensionComponent::USuspensionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USuspensionComponent::BeginPlay()
{
	UPrimitiveComponent* RootComponent = (UPrimitiveComponent*)GetAttachmentRootActor()->GetRootComponent();
	if (RootComponent != NULL)
	{
		BodyInstance = RootComponent->GetBodyInstance();
	}
	PreviousDistance = SuspensionLength;
}

FHitResult USuspensionComponent::Trace(FVector TraceStart, FVector TraceEnd)
{
	FHitResult Hit(ForceInit);
	FCollisionQueryParams TraceParams(true);
	FCollisionObjectQueryParams ObjectParams = ECC_WorldStatic | ECC_WorldDynamic | ECC_Visibility;
	TraceParams.bTraceComplex = true;
	TraceParams.AddIgnoredActor(GetAttachmentRootActor());
	GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, ObjectParams, TraceParams);
	return Hit;
}

void USuspensionComponent::Update(float PhysicsDeltaTime)
{
	if (BodyInstance == NULL)
	{
		return;
	}
	// Read transform from BodyInstance as it's always up-to-date on physics steps.
	FTransform WorldTransform = BodyInstance->GetUnrealWorldTransform_AssumesLocked();

	// We need to find up vector from up-to-date transform using GetUnitAxis.
	FVector UpVector = WorldTransform.GetUnitAxis(EAxis::Z);

	// Get components World Location by transforming root objects transform with components relative location.
	FVector WorldLocation = WorldTransform.TransformPosition(RelativeLocation);

	FVector TraceEnd = WorldLocation + SuspensionLength * -UpVector;

	FHitResult Hit = Trace(WorldLocation, TraceEnd);	
	
	// If not near ground, do nothing
	if (!Hit.bBlockingHit)
	{
		PreviousDistance = 0;
		return;
	}

	float Distance = SuspensionLength - Hit.Distance;
	float Velocity = (PreviousDistance - Distance) / PhysicsDeltaTime;
	PreviousDistance = Distance;

	float SpringDamper = SpringCoeff*Distance - DamperCoeff*Velocity;

	// It's important to set bAllowSubstepping to false here as it's only meant to be used when calling AddForce from regular Tick.
	BodyInstance->AddForceAtPosition(SpringDamper * UpVector, WorldLocation, false);
}