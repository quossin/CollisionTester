// Fill out your copyright noTtice in the Description page of Project Settings.

#include "OverlapCollisionTest.h"

void UOverlapCollisionTestByChannel::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
	{
		Shape = NewObject<UCollisionTestCapsule>(this);
	}

	Super::PostInitProperties();
}

void UOverlapCollisionTestByChannel::Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const
{
	if (CollisionTesterOwner == nullptr) return;
	if (Shape == nullptr) return;
	if (PDI == nullptr) return;

	
	const FCollisionShape CollisionShape = Shape->GetCollisionShape();
	const FVector ShapeLocation = CollisionTesterOwner->GetActorLocation();
	const FRotator ShapeRotation = CollisionTesterOwner->GetActorRotation();

	switch (CollisionShape.ShapeType)
	{
	case ECollisionShape::Box:
	{
		DrawWireBox(PDI, FBox(ShapeLocation, CollisionShape.GetExtent()), FColor::Green, SDPG_World);
		break;
	}
	case  ECollisionShape::Sphere:
	{
		DrawWireSphere(PDI, ShapeLocation, FColor::Green, CollisionShape.GetSphereRadius(), 8, SDPG_World);
		break;
	}
	case ECollisionShape::Capsule:
	{
		FVector X, Y, Z;
		FRotationMatrix RotationMatrix(ShapeRotation);
		RotationMatrix.GetScaledAxes(X, Y, Z);

		DrawWireCapsule(PDI, ShapeLocation, X, Y, Z, FColor::Green, CollisionShape.GetCapsuleRadius(), CollisionShape.GetCapsuleHalfHeight(), 8, SDPG_World);
		break;
	}
	}

}