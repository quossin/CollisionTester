// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionTesterActor.h"
#include "SceneManagement.h"

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
}

void ACollisionTesterActor::PostInitProperties()
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && !(GetOuter() && GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject)))
	{
		CollisionTest = NewObject<UTraceCollsionTest>(this);
	}

	Super::PostInitProperties();
}

void UTraceCollsionTest::Draw(ACollisionTesterActor* CollisionTesterOwner, FPrimitiveDrawInterface* PDI) const
{
	if (CollisionTesterOwner == nullptr) return;
	if (PDI == nullptr) return;
	if (CollisionTesterOwner->GetWorld() == nullptr) return;


	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CollisionTesterOwner);

	const FVector TraceStart = CollisionTesterOwner->GetActorLocation();
	const FVector TraceEnd = TraceStart + CollisionTesterOwner->GetActorForwardVector() * Length;

	bool bHasHit = CollisionTesterOwner->GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);

	PDI->DrawLine(TraceStart, TraceEnd, FColor::Green, SDPG_Foreground, 1.f);

	if (bHasHit)
	{
		DrawSphere(PDI, Hit.Location, FRotator::ZeroRotator, FVector(30), 24, 6, GEngine->ConstraintLimitMaterialPrismatic->GetRenderProxy(), SDPG_World);
	}
}
