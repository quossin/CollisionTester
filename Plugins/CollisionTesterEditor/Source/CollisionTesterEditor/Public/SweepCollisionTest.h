// Copyright Juju & Seb. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "TraceCollisionTest.h"

#include "SweepCollisionTest.generated.h"

UCLASS(BlueprintType)
class USweepCollisionTestByChannel : public UTraceCollisionTestByChannel
{
public:
	GENERATED_BODY()

	virtual void PostInitProperties() override;

	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, FPrimitiveDrawInterface* PDI) const override;
	virtual void DrawShapes(ACollisionTesterActor* CollisionTesterOwner, const FVector& ShapeLocation,
		FPrimitiveDrawInterface* PDI, const FLinearColor& ColorToUse, FCollisionShape& UsedShape) const;

	// Instanced shape data to use for the trace
	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTestShape> Shape;
};
