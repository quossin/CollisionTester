// Copyright Juju & Seb. All Rights Reserved.

#include "SweepCollisionTest.h"

#include "CollisionTestShapes.h"
#include "CollisionTesterActor.h"

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

	const FTransform StartTransform = CollisionTesterOwner->GetActorTransform();
	const FVector TraceStart = StartTransform.GetLocation();
	const FVector TraceEnd = CollisionTesterOwner->GetTraceEndTransform().GetLocation();
	const FQuat TraceShapeQuat = StartTransform.GetRotation();
	const FTransform EndTransform(TraceShapeQuat, TraceEnd);

	const FCollisionShape& CollisionShape = Shape->GetCollisionShape();

	// TODO - Support drawing lines between shape for better visualization
	if (!bMulti)
	{
		FHitResult Hit;
		const bool bHasHit = CollisionTesterOwner->GetWorld()->SweepSingleByChannel(Hit, TraceStart, TraceEnd, TraceShapeQuat, TraceChannelProperty, CollisionShape, QueryParams, ResponseParams);
		FColor ColorToUse = bHasHit ? FColor::Red : FColor::Green;

		if (bHasHit)
		{
			DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialX->GetRenderProxy());
			ColorToUse = Hit.bBlockingHit ? FColor::Red : FColor::Blue;
		}

		Shape->DrawShape(PDI, StartTransform, ColorToUse);
		Shape->DrawShape(PDI, EndTransform, ColorToUse);
	}
	else
	{
		TArray<FHitResult> OutHits;
		CollisionTesterOwner->GetWorld()->SweepMultiByChannel(OutHits, TraceStart, TraceEnd, FQuat::Identity,
			TraceChannelProperty, CollisionShape, QueryParams, ResponseParams);

		if (OutHits.Num() == 0)
		{
			Shape->DrawShape(PDI, StartTransform, FColor::Green);
			Shape->DrawShape(PDI, EndTransform, FColor::Green);
		}
		else
		{
			const FHitResult& LastHit = OutHits[OutHits.Num() - 1];
			const FColor ColorToUse = LastHit.bBlockingHit ? FColor::Red : FColor::Blue;
			Shape->DrawShape(PDI, StartTransform, ColorToUse);
			bool bHasBlockingHit = false;

			for (const FHitResult& Hit : OutHits)
			{
				const FTransform HitTransform(TraceShapeQuat, Hit.Location);
				if (Hit.bBlockingHit)
				{
					Shape->DrawShape(PDI, HitTransform, FColor::Red);
					bHasBlockingHit = true;
				}
				else
				{
					Shape->DrawShape(PDI, HitTransform, FColor::Blue);
				}
			}

			const FColor EndColor = bHasBlockingHit ? FColor::White : FColor::Green;
			Shape->DrawShape(PDI, EndTransform, EndColor);
		}
	}
}

void USweepCollisionTestByObjectType::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
	{
		Shape = NewObject<UCollisionTestCapsule>(this);
	}

	Super::PostInitProperties();
}

void USweepCollisionTestByObjectType::Draw(ACollisionTesterActor* CollisionTesterOwner, FPrimitiveDrawInterface* PDI) const
{
	if (CollisionTesterOwner == nullptr) return;
	if (PDI == nullptr) return;
	if (CollisionTesterOwner->GetWorld() == nullptr) return;

	FCollisionQueryParams QueryParams = GetQueryParams(*CollisionTesterOwner);
	FCollisionObjectQueryParams CollisionObjectQueryParams = CollisionTestByObjectMode->GetCollisionObjectQueryParams();
	CollisionObjectQueryParams.IgnoreMask = static_cast<uint8>(FilterFlags);

	const FTransform StartTransform = CollisionTesterOwner->GetActorTransform();
	const FVector TraceStart = StartTransform.GetLocation();
	const FVector TraceEnd = CollisionTesterOwner->GetTraceEndTransform().GetLocation();
	const FQuat TraceShapeQuat = StartTransform.GetRotation();
	const FTransform EndTransform(TraceShapeQuat, TraceEnd);

	const FCollisionShape& CollisionShape = Shape->GetCollisionShape();

	// TODO - Support drawing lines between shape for better visualization
	if (!bMulti)
	{
		FHitResult Hit;
		const bool bHasHit = CollisionTesterOwner->GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, TraceShapeQuat, CollisionObjectQueryParams, CollisionShape, QueryParams);
		FColor ColorToUse = bHasHit ? FColor::Red : FColor::Green;

		if (bHasHit)
		{
			DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialX->GetRenderProxy());
			ColorToUse = Hit.bBlockingHit ? FColor::Red : FColor::Blue;
		}

		Shape->DrawShape(PDI, StartTransform, ColorToUse);
		Shape->DrawShape(PDI, EndTransform, ColorToUse);
	}
	else
	{
		TArray<FHitResult> OutHits;
		CollisionTesterOwner->GetWorld()->SweepMultiByObjectType(OutHits, TraceStart, TraceEnd, TraceShapeQuat, CollisionObjectQueryParams, CollisionShape, QueryParams);

		if (OutHits.Num() == 0)
		{
			Shape->DrawShape(PDI, StartTransform, FColor::Green);
			Shape->DrawShape(PDI, EndTransform, FColor::Green);
		}
		else
		{
			const FHitResult& LastHit = OutHits[OutHits.Num() - 1];
			const FColor ColorToUse = LastHit.bBlockingHit ? FColor::Red : FColor::Blue;
			Shape->DrawShape(PDI, StartTransform, ColorToUse);
			bool bHasBlockingHit = false;

			for (const FHitResult& Hit : OutHits)
			{
				const FTransform HitTransform(TraceShapeQuat, Hit.Location);
				if (Hit.bBlockingHit)
				{
					Shape->DrawShape(PDI, HitTransform, FColor::Red);
					bHasBlockingHit = true;
				}
				else
				{
					Shape->DrawShape(PDI, HitTransform, FColor::Blue);
				}
			}

			const FColor EndColor = bHasBlockingHit ? FColor::White : FColor::Green;
			Shape->DrawShape(PDI, EndTransform, EndColor);
		}
	}
}
