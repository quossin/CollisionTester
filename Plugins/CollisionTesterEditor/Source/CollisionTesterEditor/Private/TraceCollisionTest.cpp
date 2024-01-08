// Copyright Juju & Seb. All Rights Reserved.

#include "TraceCollisionTest.h"

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
			DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialX->GetRenderProxy());
		}
	}
	else
	{
		TArray<struct FHitResult> OutHits;
		CollisionTesterOwner->GetWorld()->LineTraceMultiByChannel(OutHits, TraceStart, TraceEnd, TraceChannelProperty, QueryParams, ResponseParams);

		if (OutHits.Num() == 0)
		{
			PDI->DrawLine(TraceStart, TraceEnd, FColor::Green, SDPG_Foreground, 1.f);
		}
		else
		{
			const FLinearColor StartColorToUse = OutHits[0].bBlockingHit ? FColor::Red : FColor::Blue;
			PDI->DrawLine(TraceStart, OutHits[0].Location, StartColorToUse, SDPG_Foreground, 1.f);
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
			const FVector& LastHitLoc = LastHit.Location;
			const FLinearColor EndColorToUse = LastHit.bBlockingHit ? FColor::Red : FColor::Blue;
			PDI->DrawLine(LastHitLoc, TraceEnd, EndColorToUse, SDPG_Foreground, 1.f);
		}
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
		if (!bHasHit)
		{
			PDI->DrawLine(TraceStart, TraceEnd, FColor::Green, SDPG_Foreground, 1.f);
		}
		else
		{
			PDI->DrawLine(TraceStart, Hit.Location, FColor::Green, SDPG_Foreground, 1.f);
			PDI->DrawLine(Hit.Location, TraceEnd, FColor::Red, SDPG_Foreground, 1.f);
			DrawHit(PDI, Hit, GEngine->ConstraintLimitMaterialX->GetRenderProxy());
		}
	}
	else
	{
		TArray<struct FHitResult> OutHits;
		CollisionTesterOwner->GetWorld()->LineTraceMultiByObjectType(OutHits, TraceStart, TraceEnd, CollisionObjectQueryParams, QueryParams);

		if (OutHits.Num() == 0)
		{
			PDI->DrawLine(TraceStart, TraceEnd, FColor::Green, SDPG_Foreground, 1.f);
		}
		else
		{
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

			const FVector& LastHitLoc = OutHits[OutHits.Num() - 1].Location;
			PDI->DrawLine(TraceStart, LastHitLoc, FColor::Green, SDPG_Foreground, 1.f);
			PDI->DrawLine(LastHitLoc, TraceEnd, FColor::Red, SDPG_Foreground, 1.f);
		}
	}
}

