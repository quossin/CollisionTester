// Fill out your copyright noTtice in the Description page of Project Settings.

#include "CollisionTestShapes.h"

FCollisionShape UCollisionTestSphere::GetCollisionShape() const
{
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	return Shape;
}


FCollisionShape UCollisionTestBox::GetCollisionShape() const
{
	FCollisionShape Shape;
	Shape.SetBox(FVector3f(HalfExtentX, HalfExtentY, HalfExtentZ));
	return Shape;
}


FCollisionShape UCollisionTestCapsule::GetCollisionShape() const
{
	FCollisionShape Shape;
	Shape.SetCapsule(Radius, HalfHeight);
	return Shape;
}
