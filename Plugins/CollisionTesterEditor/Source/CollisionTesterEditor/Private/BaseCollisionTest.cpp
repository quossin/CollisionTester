// Copyright Juju & Seb. All Rights Reserved.

#include "BaseCollisionTest.h"

UObjectTypeListCollisionTestByObjectMode::UObjectTypeListCollisionTestByObjectMode()
{
	ObjectTypes.Add(ObjectTypeQuery1);
}

FCollisionObjectQueryParams UObjectTypeListCollisionTestByObjectMode::GetCollisionObjectQueryParams() const
{
	return FCollisionObjectQueryParams(ObjectTypes);
}

FCollisionObjectQueryParams UAllTypeListCollisionTestByObjectMode::GetCollisionObjectQueryParams() const
{
	switch (CollisionTestByObjectMode)
	{
	case ECollisionTestByObjectMode::AllObjects:
		return FCollisionObjectQueryParams(FCollisionQueryFlag::Get().GetAllObjectsQueryFlag());
	case ECollisionTestByObjectMode::AllStaticObjects:
		return FCollisionObjectQueryParams(FCollisionQueryFlag::Get().GetAllStaticObjectsQueryFlag());
	case ECollisionTestByObjectMode::AllDynamicObjects:
		return FCollisionObjectQueryParams(FCollisionQueryFlag::Get().GetAllDynamicObjectsQueryFlag());
	}

	return FCollisionObjectQueryParams();
}

void UBaseCollisionTest::DrawHit(class FPrimitiveDrawInterface* PDI, const FHitResult& Hit, const FMaterialRenderProxy* MaterialRenderProxy) const
{
	DrawSphere(PDI, Hit.Location, FRotator::ZeroRotator, FVector(10), 24, 6, MaterialRenderProxy, SDPG_World);
}

FCollisionQueryParams UBaseCollisionTest::GetQueryParams(const AActor& Owner) const
{
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = bTraceComplex;
	QueryParams.bFindInitialOverlaps = bFindInitialOverlaps;
	QueryParams.bIgnoreBlocks = bIgnoreBlocks;
	QueryParams.bIgnoreTouches = bIgnoreTouches;
	QueryParams.bSkipNarrowPhase = bSkipNarrowPhase;
	QueryParams.bTraceIntoSubComponents = bTraceIntoSubComponents;
	QueryParams.AddIgnoredActor(&Owner);

	return QueryParams;
}

