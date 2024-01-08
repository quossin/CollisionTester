// Copyright Juju & Seb. All Rights Reserved.

#include "CollisionTestShapes.h"


FCollisionShape UCollisionTestSphere::GetCollisionShape() const
{
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	return Shape;
}

void UCollisionTestSphere::DrawShape(FPrimitiveDrawInterface* PDI, const FTransform& Transform, const FColor& Color) const
{
	DrawWireSphere(PDI, Transform.GetLocation(), Color, Radius, 8, SDPG_World);
}

FCollisionShape UCollisionTestBox::GetCollisionShape() const
{
	FCollisionShape Shape;
	Shape.SetBox(FVector3f(HalfExtentX, HalfExtentY, HalfExtentZ));
	return Shape;
}

void UCollisionTestBox::DrawShape(FPrimitiveDrawInterface* PDI, const FTransform& Transform, const FColor& Color) const
{
	FMatrix Matrix = FRotationMatrix::Make(Transform.GetRotation());
	Matrix.SetOrigin(Transform.GetLocation());

	const FVector Extent(HalfExtentX, HalfExtentY, HalfExtentZ);

	const FBox Box = FBox::BuildAABB(FVector::ZeroVector, Extent);

	DrawWireBox(PDI, Matrix, Box, Color, SDPG_World);
}

FCollisionShape UCollisionTestCapsule::GetCollisionShape() const
{
	FCollisionShape Shape;
	Shape.SetCapsule(Radius, HalfHeight);
	return Shape;
}

void UCollisionTestCapsule::DrawShape(FPrimitiveDrawInterface* PDI, const FTransform& Transform, const FColor& Color) const
{
	const FMatrix RotationMatrix = FRotationMatrix::Make(Transform.GetRotation());
	FVector X, Y, Z;
	RotationMatrix.GetScaledAxes(X, Y, Z);

	DrawWireCapsule(PDI, Transform.GetLocation(), X, Y, Z, Color, Radius, HalfHeight, 8, SDPG_World);
}

