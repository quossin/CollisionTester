// Copyright Juju & Seb. All Rights Reserved.

#include "OverlapCollisionTest.h"

#include "Engine/OverlapResult.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/PrimitiveComponent.h"
#include "SceneManagement.h"

namespace CollisionTestUtil
{
	namespace Overlap
	{
		void DrawOverlap(const UBaseCollisionTest& CollisionTest, const TArray<FOverlapResult>& OutOverlaps, const FTransform& ShapeTransform, const UBaseCollisionTestShape& Shape, FPrimitiveDrawInterface* PDI)
		{

			bool bHasBlockingHit = false;

			int32 Index = 0;
			for (const FOverlapResult& OverlapResult : OutOverlaps)
			{
				bHasBlockingHit |= OverlapResult.bBlockingHit;

				if (UPrimitiveComponent* PrimitiveComponent = OverlapResult.GetComponent())
				{
					const FMaterialRenderProxy* MaterialRenderProxy = OverlapResult.bBlockingHit ? GEngine->ConstraintLimitMaterialX->GetRenderProxy() : GEngine->ConstraintLimitMaterialZ->GetRenderProxy();
					DrawSphere(PDI, PrimitiveComponent->GetComponentLocation(), FRotator::ZeroRotator, FVector(30), 24, 6, MaterialRenderProxy, SDPG_World);

					const FBoxSphereBounds BoxSphereBounds = PrimitiveComponent->Bounds;
					const FBox BoundsBox = FBox::BuildAABB(BoxSphereBounds.Origin, BoxSphereBounds.BoxExtent);
					const FColor Color = bHasBlockingHit ? FColor::Red : FColor::Blue;
					DrawWireBox(PDI, BoundsBox, Color, SDPG_World);
					CollisionTest.PrintHitInfo(OverlapResult, Index++);
				}
			}

			FColor Color = FColor::Green;

			if (OutOverlaps.Num() > 0)
			{
				Color = bHasBlockingHit ? FColor::Red : FColor::Blue;
			}

			Shape.DrawShape(PDI, ShapeTransform, Color);
		}
	}
}

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
	if (CollisionTesterOwner->GetWorld() == nullptr) return;
	if (Shape == nullptr) return;
	if (PDI == nullptr) return;
	
	const FCollisionShape CollisionShape = Shape->GetCollisionShape();
	const FTransform ShapeTransform = CollisionTesterOwner->GetActorTransform();

	FCollisionQueryParams QueryParams = GetQueryParams(*CollisionTesterOwner);

	FCollisionResponseContainer CollisionResponseContainer;
	CollisionResponseContainer.SetAllChannels(DefaultResponse);

	for (const FCollisionTestResponsePair& ResponsePair : ResponsePairs)
	{
		CollisionResponseContainer.SetResponse(ResponsePair.TraceChannel, ResponsePair.Response);
	}

	TArray<FOverlapResult> OutOverlaps;

	CollisionTesterOwner->GetWorld()->OverlapMultiByChannel(OutOverlaps, ShapeTransform.GetLocation(), ShapeTransform.GetRotation(), TraceChannel, CollisionShape, QueryParams, CollisionResponseContainer);
	CollisionTestUtil::Overlap::DrawOverlap(*this, OutOverlaps, ShapeTransform, *Shape, PDI);
}

void UOverlapCollisionTestByObjectType::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
	{
		CollisionTestByObjectMode = NewObject<UObjectTypeListCollisionTestByObjectMode>(this);
		Shape = NewObject<UCollisionTestCapsule>(this);
	}

	Super::PostInitProperties();
}

void UOverlapCollisionTestByObjectType::Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const
{
	if (CollisionTesterOwner == nullptr) return;
	if (CollisionTesterOwner->GetWorld() == nullptr) return;
	if (Shape == nullptr) return;
	if (PDI == nullptr) return;

	const FCollisionShape CollisionShape = Shape->GetCollisionShape();
	const FTransform ShapeTransform = CollisionTesterOwner->GetActorTransform();

	FCollisionQueryParams QueryParams = GetQueryParams(*CollisionTesterOwner);
	FCollisionObjectQueryParams CollisionObjectQueryParams = CollisionTestByObjectMode->GetCollisionObjectQueryParams();
	CollisionObjectQueryParams.IgnoreMask = static_cast<uint8>(FilterFlags);

	TArray<FOverlapResult> OutOverlaps;

	CollisionTesterOwner->GetWorld()->OverlapMultiByObjectType(OutOverlaps, ShapeTransform.GetLocation(), ShapeTransform.GetRotation(), CollisionObjectQueryParams, CollisionShape, QueryParams);
	CollisionTestUtil::Overlap::DrawOverlap(*this, OutOverlaps, ShapeTransform, *Shape, PDI);

}

