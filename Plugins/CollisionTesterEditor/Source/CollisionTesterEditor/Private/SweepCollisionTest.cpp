// Copyright Juju & Seb. All Rights Reserved.

#include "SweepCollisionTest.h"

void USweepCollisionTestByChannel::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
	{
		Shape = NewObject<UCollisionTestCapsule>(this);
	}

	Super::PostInitProperties();
}

void USweepCollisionTestByChannel::Draw(ACollisionTesterActor* CollisionTesterOwner, FPrimitiveDrawInterface* PDI) const
{
	if (CollisionTesterOwner == nullptr) return;
	if (PDI == nullptr) return;
	if (CollisionTesterOwner->GetWorld() == nullptr) return;

	FCollisionQueryParams QueryParams = GetQueryParams(*CollisionTesterOwner);

	FCollisionResponseContainer CollisionResponseContainer;
	CollisionResponseContainer.SetAllChannels(DefaultResponse);

	for (const FCollisionTestResponsePair& ResponsePair : ResponsePairs)
	{
		CollisionResponseContainer.SetResponse(ResponsePair.TraceChannel, ResponsePair.Response);
	}

	FCollisionResponseParams ResponseParams(CollisionResponseContainer);

	const FVector TraceStart = CollisionTesterOwner->GetActorLocation();
	const FVector TraceEnd = CollisionTesterOwner->GetTraceEndTransform().GetLocation();

	FCollisionShape CollisionShape = Shape->GetCollisionShape();

	// TODO - Support drawing lines between shape for better visualization
	if (!bMulti)
	{
		FHitResult Hit;
		const bool bHasHit = CollisionTesterOwner->GetWorld()->SweepSingleByChannel(Hit, TraceStart, TraceEnd,
			FQuat::Identity, TraceChannelProperty, CollisionShape, QueryParams, ResponseParams);
		FLinearColor ColorToUse = bHasHit ? FColor::Red : FColor::Green;

		if (bHasHit)
		{
			DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialX->GetRenderProxy());
			ColorToUse = Hit.bBlockingHit ? FColor::Red : FColor::Blue;
		}
		DrawShapes(CollisionTesterOwner, TraceStart, PDI, ColorToUse, CollisionShape);
		DrawShapes(CollisionTesterOwner, TraceEnd, PDI, ColorToUse, CollisionShape);
	}
	else
	{
		TArray<FHitResult> OutHits;
		CollisionTesterOwner->GetWorld()->SweepMultiByChannel(OutHits, TraceStart, TraceEnd, FQuat::Identity,
			TraceChannelProperty, CollisionShape, QueryParams, ResponseParams);

		if (OutHits.Num() == 0)
		{
			DrawShapes(CollisionTesterOwner, TraceStart, PDI, FColor::Green, CollisionShape);
			DrawShapes(CollisionTesterOwner, TraceEnd, PDI, FColor::Green, CollisionShape);
		}
		else
		{
			const FLinearColor StartColorToUse = OutHits[0].bBlockingHit ? FColor::Red : FColor::Blue;
			DrawShapes(CollisionTesterOwner, TraceStart, PDI, StartColorToUse, CollisionShape);
			for (const FHitResult& Hit : OutHits)
			{
				if (Hit.bBlockingHit)
				{
					DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialX->GetRenderProxy());
				}
				else
				{
					DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialZ->GetRenderProxy());
				}
			}

			const FHitResult& LastHit = OutHits[OutHits.Num() - 1];
			const FLinearColor EndColorToUse = LastHit.bBlockingHit ? FColor::Red : FColor::Blue;
			DrawShapes(CollisionTesterOwner, TraceEnd, PDI, EndColorToUse, CollisionShape);
		}
	}
}

void USweepCollisionTestByChannel::DrawShapes(ACollisionTesterActor* CollisionTesterOwner, const FVector& ShapeLocation, FPrimitiveDrawInterface* PDI,
	const FLinearColor& ColorToUse, FCollisionShape& UsedShape) const
{
	const FTransform EndOfTrace = CollisionTesterOwner->GetTraceEndTransform();
	switch (UsedShape.ShapeType)
	{
	case ECollisionShape::Box:
	{
		const FVector BoxStartMin = ShapeLocation - UsedShape.GetExtent();
		const FVector BoxStartMax = ShapeLocation + UsedShape.GetExtent();

		DrawWireBox(PDI, FBox(BoxStartMin, BoxStartMax), ColorToUse, 8, SDPG_Foreground, 1.f);
		break;
	}
	case ECollisionShape::Sphere:
	{
		DrawWireSphere(PDI, ShapeLocation, ColorToUse, UsedShape.GetSphereRadius(), 8, SDPG_Foreground, 1.f);
		DrawWireSphere(PDI, ShapeLocation, ColorToUse, UsedShape.GetSphereRadius(), 8, SDPG_Foreground, 1.f);
		break;
	}
	case ECollisionShape::Capsule:
	{
		const FMatrix RotationMatrix = FRotationMatrix::Make(CollisionTesterOwner->GetActorRotation());
		FVector X, Y, Z;
		RotationMatrix.GetScaledAxes(X, Y, Z);
		DrawWireCapsule(PDI, ShapeLocation, X, Y, Z, ColorToUse, UsedShape.GetCapsuleRadius(),
			UsedShape.GetCapsuleHalfHeight(), 8, SDPG_Foreground, 1.f);

		const FMatrix RotationMatrixEnd = FRotationMatrix::Make(EndOfTrace.GetRotation());
		FVector XEnd, YEnd, ZEnd;
		RotationMatrix.GetScaledAxes(XEnd, YEnd, ZEnd);
		DrawWireCapsule(PDI, ShapeLocation, XEnd, YEnd, ZEnd, ColorToUse, UsedShape.GetCapsuleRadius(),
			UsedShape.GetCapsuleHalfHeight(), 8, SDPG_Foreground, 1.f);
		break;
	}
	case ECollisionShape::Line:
	default:
	{
		// TODO - Warning message ?	
	}
	}
}