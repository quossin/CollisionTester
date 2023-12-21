// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionTesterActor.h"
#include "CollisionTestShapes.h"
#include "SceneManagement.h"
#include "Components/BillboardComponent.h"

#include "Components/SceneComponent.h"


void FCollisionTesterComponentVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	if (AActor* ComponentOwner = (Component ? Component->GetOwner() : nullptr))
	{
		if (ACollisionTesterActor* CollisionTesterActor = Cast<ACollisionTesterActor>(ComponentOwner))
		{
			if (CollisionTesterActor->CollisionTest)
			{
				CollisionTesterActor->CollisionTest->Draw(CollisionTesterActor, PDI);
			}
		}
	}
}

// Sets default values
ACollisionTesterActor::ACollisionTesterActor()
{
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));
	CollisionTesterComponent = CreateDefaultSubobject<UCollisionTesterComponent>(TEXT("CollisionTesterComponent"));

	Sprite = CreateEditorOnlyDefaultSubobject<UBillboardComponent>(TEXT("Sprite"));
	bIsEditorOnlyActor = true;

	EndOfTrace.SetLocation({300.f, 0.f, 0.f});

#if WITH_EDITORONLY_DATA
	if (!IsRunningCommandlet())
	{
		// Structure to hold one-time initialization
		struct FConstructorStatics
		{
			ConstructorHelpers::FObjectFinderOptional<UTexture2D> SpriteTextureObject;
			FName ID_CollisionTester;
			FText NAME_CollisionTester;
			FConstructorStatics()
				: SpriteTextureObject(TEXT("/Engine/EditorResources/S_NavP"))
				, ID_CollisionTester(TEXT("CollisionTester"))
				, NAME_CollisionTester(NSLOCTEXT("SpriteCategory", "CollisionTester", "CollisionTester"))
			{
			}
		};
		static FConstructorStatics ConstructorStatics;

		if (Sprite)
		{
			Sprite->Sprite = ConstructorStatics.SpriteTextureObject.Get();
			Sprite->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
			Sprite->bHiddenInGame = true;
			Sprite->SpriteInfo.Category = ConstructorStatics.ID_CollisionTester;
			Sprite->SpriteInfo.DisplayName = ConstructorStatics.NAME_CollisionTester;
			Sprite->SetupAttachment(RootComponent);
			Sprite->SetUsingAbsoluteScale(true);
			Sprite->bIsScreenSizeScaled = true;
		}
	}
#endif // WITH_EDITORONLY_DATA
}

void ACollisionTesterActor::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
	{
		CollisionTest = NewObject<UTraceCollisionTestByChannel>(this);
	}

	Super::PostInitProperties();
}

FTransform ACollisionTesterActor::GetTraceEndTransform() const
{
	return FTransform(EndOfTrace.GetRotation(), GetActorTransform().TransformPosition(EndOfTrace.GetLocation()));
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
			const FLinearColor StartColorToUse = OutHits[0].bBlockingHit ?  FColor::Red : FColor::Blue;
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
			const FLinearColor EndColorToUse = LastHit.bBlockingHit ?  FColor::Red : FColor::Blue;
			PDI->DrawLine(LastHitLoc, TraceEnd, EndColorToUse, SDPG_Foreground, 1.f);
		}
	}
}

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
		DrawShapes(CollisionTesterOwner, TraceStart, PDI,ColorToUse, CollisionShape);
		DrawShapes(CollisionTesterOwner, TraceEnd, PDI,ColorToUse, CollisionShape);
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
			const FLinearColor StartColorToUse = OutHits[0].bBlockingHit ?  FColor::Red : FColor::Blue;
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
			const FLinearColor EndColorToUse = LastHit.bBlockingHit ?  FColor::Red : FColor::Blue;
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

void UTraceCollisionTestByObjectType::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
	{
		CollisionTestByObjectMode = NewObject<UObjectTypeListCollisionTestByObjectMode>(this);
	}

	Super::PostInitProperties();
}