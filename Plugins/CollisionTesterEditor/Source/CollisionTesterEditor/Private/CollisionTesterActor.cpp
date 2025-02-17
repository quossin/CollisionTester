// Copyright Juju & Seb. All Rights Reserved.
#include "CollisionTesterActor.h"

#include "BaseCollisionTest.h"
#include "CollisionTesterActor.h"
#include "CollisionTestShapes.h"
#include "Components/BillboardComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Texture2D.h"
#include "SceneManagement.h"
#include "SweepCollisionTest.h"
#include "UObject/ConstructorHelpers.h"

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
