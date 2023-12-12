// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionTesterActor.h"
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
		CollisionTest = NewObject<UTraceCollsionTestByChannel>(this);
	}

	Super::PostInitProperties();
}

void UBaseCollisionTest::DrawHit(class FPrimitiveDrawInterface* PDI, const FHitResult& Hit, const FMaterialRenderProxy* MaterialRenderProxy) const
{
	DrawSphere(PDI, Hit.Location, FRotator::ZeroRotator, FVector(10), 24, 6, MaterialRenderProxy, SDPG_World);
}

FCollisionQueryParams UBaseCollisionTest::GetQueryParams(AActor& Owner) const
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

void UTraceCollsionTestByChannel::Draw(ACollisionTesterActor* CollisionTesterOwner, FPrimitiveDrawInterface* PDI) const
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
	const FVector TraceEnd = TraceStart + CollisionTesterOwner->GetActorForwardVector() * Length;

	if (!bMulti)
	{
		FHitResult Hit;
		bool bHasHit = CollisionTesterOwner->GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams, ResponseParams);
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
		CollisionTesterOwner->GetWorld()->LineTraceMultiByChannel(OutHits, TraceStart, TraceEnd, TraceChannelProperty, QueryParams, ResponseParams);

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


void UTraceCollsionTestByObjectType::Draw(ACollisionTesterActor* CollisionTesterOwner, FPrimitiveDrawInterface* PDI) const
{
	if (CollisionTesterOwner == nullptr) return;
	if (PDI == nullptr) return;
	if (CollisionTesterOwner->GetWorld() == nullptr) return;
	if (CollisionTestByObjectMode == nullptr) return;

	FCollisionQueryParams QueryParams = GetQueryParams(*CollisionTesterOwner);
	FCollisionObjectQueryParams CollisionObjectQueryParams = CollisionTestByObjectMode->GetCollisionObjectQueryParams();


	const FVector TraceStart = CollisionTesterOwner->GetActorLocation();
	const FVector TraceEnd = TraceStart + CollisionTesterOwner->GetActorForwardVector() * Length;


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

void UTraceCollsionTestByObjectType::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
	{
		CollisionTestByObjectMode = NewObject<UObjectTypeListCollisionTestByObjectMode>(this);
	}

	Super::PostInitProperties();
}