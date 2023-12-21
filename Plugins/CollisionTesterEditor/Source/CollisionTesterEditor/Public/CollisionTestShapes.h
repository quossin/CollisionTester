// Fill out your copyright noTtice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CollisionTestShapes.generated.h"

UCLASS(Abstract, EditInlineNew, CollapseCategories)
class UBaseCollisionTestShape : public UObject
{
public:
	GENERATED_BODY()
	virtual FCollisionShape GetCollisionShape() const PURE_VIRTUAL(UBaseCollisionTestShape::GetCollisionShape, return FCollisionShape(););
};

UCLASS(EditInlineNew, CollapseCategories)
class UCollisionTestSphere : public UBaseCollisionTestShape
{
public:
	GENERATED_BODY()
	virtual FCollisionShape GetCollisionShape() const;

	UPROPERTY(EditInstanceOnly, Category = "Params", meta = (UIMin = 0, ClampMin = 0))
	float Radius = 50.f;

};

UCLASS(EditInlineNew, CollapseCategories)
class UCollisionTestBox : public UBaseCollisionTestShape
{
public:
	GENERATED_BODY()
	virtual FCollisionShape GetCollisionShape() const;

	UPROPERTY(EditInstanceOnly, Category = "Params", meta = (UIMin = 0, ClampMin = 0))
	float HalfExtentX = 50.f;

	UPROPERTY(EditInstanceOnly, Category = "Params", meta = (UIMin = 0, ClampMin = 0))
	float HalfExtentY = 50.f;

	UPROPERTY(EditInstanceOnly, Category = "Params", meta = (UIMin = 0, ClampMin = 0))
	float HalfExtentZ = 50.f;
};

UCLASS(EditInlineNew, CollapseCategories)
class UCollisionTestCapsule : public UBaseCollisionTestShape
{
public:
	GENERATED_BODY()
	virtual FCollisionShape GetCollisionShape() const;

	UPROPERTY(EditInstanceOnly, Category = "Params", meta = (UIMin = 0, ClampMin = 0))
	float Radius = 34.f;

	UPROPERTY(EditInstanceOnly, Category = "Params", meta = (UIMin = 0, ClampMin = 0))
	float HalfHeight = 88.f;
};
