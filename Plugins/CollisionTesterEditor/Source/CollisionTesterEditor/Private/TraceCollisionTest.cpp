// Copyright Juju & Seb. All Rights Reserved.

#include "TraceCollisionTest.h"

#include "CollisionTesterActor.h"


namespace CollisionTestUtil
{
	namespace Trace
	{
		void DrawTraceLine(const UBaseCollisionTest& CollisionTest, const FHitResult& Hit, bool bHasHit, const FVector& TraceStart, const FVector& TraceEnd, FPrimitiveDrawInterface* PDI)
		{
			FLinearColor ColorToUse = bHasHit ? FColor::Red : FColor::Green;

			if (!bHasHit)
			{
				ColorToUse = Hit.bBlockingHit ? FColor::Red : FColor::Blue;
				PDI->DrawLine(TraceStart, TraceEnd, ColorToUse, SDPG_Foreground, 1.f);
			}
			else
			{
				PDI->DrawLine(TraceStart, Hit.Location, FColor::Green, SDPG_Foreground, 1.f);
				FLinearColor EndColorToUse = Hit.bBlockingHit ? FColor::Red : FColor::Blue;
				PDI->DrawLine(Hit.Location, TraceEnd, EndColorToUse, SDPG_Foreground, 1.f);
				CollisionTest.DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialX->GetRenderProxy());

				CollisionTest.PrintHitInfo(Hit);
			}
		}

		void DrawTraceLine(const UBaseCollisionTest& CollisionTest, const TArray<FHitResult>& Hits, const FVector& TraceStart, const FVector& TraceEnd, FPrimitiveDrawInterface* PDI)
		{
			if (Hits.Num() == 0)
			{
				PDI->DrawLine(TraceStart, TraceEnd, FColor::Green, SDPG_Foreground, 1.f);
			}
			else
			{
				const FLinearColor StartColorToUse = Hits[0].bBlockingHit ? FColor::Red : FColor::Blue;
				PDI->DrawLine(TraceStart, Hits[0].Location, StartColorToUse, SDPG_Foreground, 1.f);

				FHitResult* PreviousHit = nullptr;

				int32 Index = 0;
				for (const FHitResult& Hit : Hits)
				{
					if (Hit.bBlockingHit)
					{
						CollisionTest.DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialX->GetRenderProxy());
					}
					else
					{
						CollisionTest.DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialZ->GetRenderProxy());
					}

					CollisionTest.PrintHitInfo(Hit, Index++);
				}

				const FHitResult& LastHit = Hits[Hits.Num() - 1];
				const FVector& LastHitLoc = LastHit.Location;

				if (Hits.Num() > 1)
				{
					const FLinearColor EndColorToUse = LastHit.bBlockingHit ? FColor::Red : FColor::Blue;
					PDI->DrawLine(Hits[0].Location, LastHitLoc, EndColorToUse, SDPG_Foreground, 1.f);
				}

				if (!LastHit.bBlockingHit)
				{
					PDI->DrawLine(LastHitLoc, TraceEnd, FColor::Blue, SDPG_Foreground, 1.f);
				}
			}
		}
	}
}

void UTraceCollisionTestByChannel::Draw(ACollisionTesterActor* CollisionTesterOwner, FPrimitiveDrawInterface* PDI) const
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

	if (!bMulti)
	{
		FHitResult Hit;
		bool bHasHit = CollisionTesterOwner->GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd,
			TraceChannelProperty, QueryParams, ResponseParams);
		CollisionTestUtil::Trace::DrawTraceLine(*this, Hit, bHasHit, TraceStart, TraceEnd, PDI);
	}
	else
	{
		TArray<FHitResult> OutHits;
		CollisionTesterOwner->GetWorld()->LineTraceMultiByChannel(OutHits, TraceStart, TraceEnd, TraceChannelProperty, QueryParams, ResponseParams);
		CollisionTestUtil::Trace::DrawTraceLine(*this, OutHits, TraceStart, TraceEnd, PDI);
	}
}

void UTraceCollisionTestByObjectType::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
	{
		CollisionTestByObjectMode = NewObject<UObjectTypeListCollisionTestByObjectMode>(this);
	}

	Super::PostInitProperties();
}

void UTraceCollisionTestByObjectType::Draw(ACollisionTesterActor* CollisionTesterOwner, FPrimitiveDrawInterface* PDI) const
{
	if (CollisionTesterOwner == nullptr) return;
	if (PDI == nullptr) return;
	if (CollisionTesterOwner->GetWorld() == nullptr) return;
	if (CollisionTestByObjectMode == nullptr) return;

	FCollisionQueryParams QueryParams = GetQueryParams(*CollisionTesterOwner);
	FCollisionObjectQueryParams CollisionObjectQueryParams = CollisionTestByObjectMode->GetCollisionObjectQueryParams();
	CollisionObjectQueryParams.IgnoreMask = static_cast<uint8>(FilterFlags);

	const FVector TraceStart = CollisionTesterOwner->GetActorLocation();
	const FVector TraceEnd = CollisionTesterOwner->GetTraceEndTransform().GetLocation();

	if (!bMulti)
	{
		FHitResult Hit;
		bool bHasHit = CollisionTesterOwner->GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, CollisionObjectQueryParams, QueryParams);
		CollisionTestUtil::Trace::DrawTraceLine(*this, Hit, bHasHit, TraceStart, TraceEnd, PDI);
	}
	else
	{
		TArray<FHitResult> OutHits;
		CollisionTesterOwner->GetWorld()->LineTraceMultiByObjectType(OutHits, TraceStart, TraceEnd, CollisionObjectQueryParams, QueryParams);
		CollisionTestUtil::Trace::DrawTraceLine(*this, OutHits, TraceStart, TraceEnd, PDI);
	}
}

