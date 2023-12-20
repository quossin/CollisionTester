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

	bool bHasBlockingHit = false;

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
		}
	}

	FColor Color = FColor::Green;

	if (OutOverlaps.Num() > 0)
	{
		Color = bHasBlockingHit ? FColor::Red : FColor::Blue;
	}

	switch (CollisionShape.ShapeType)
	{
	case ECollisionShape::Box:
	{
		FMatrix Matrix = FRotationMatrix::Make(ShapeTransform.GetRotation());
		Matrix.SetOrigin(ShapeTransform.GetLocation());

		const FBox Box = FBox::BuildAABB(FVector::ZeroVector, CollisionShape.GetExtent());

		DrawWireBox(PDI, Matrix, Box, Color, SDPG_World);
		break;
	}
	case  ECollisionShape::Sphere:
	{
		DrawWireSphere(PDI, ShapeTransform.GetLocation(), Color, CollisionShape.GetSphereRadius(), 8, SDPG_World);
		break;
	}
	case ECollisionShape::Capsule:
	{
		const FMatrix RotationMatrix = FRotationMatrix::Make(ShapeTransform.GetRotation());
		FVector X, Y, Z;
		RotationMatrix.GetScaledAxes(X, Y, Z);

		DrawWireCapsule(PDI, ShapeTransform.GetLocation(), X, Y, Z, Color, CollisionShape.GetCapsuleRadius(), CollisionShape.GetCapsuleHalfHeight(), 8, SDPG_World);
		break;
	}
	}

}