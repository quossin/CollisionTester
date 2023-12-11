// Fill out your copyright noTtice in the Description page of Project Settings.

#pragma once

#include "ComponentVisualizer.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

#include "CollisionTesterActor.generated.h"

class ActorComponent;


class FCollisionTesterComponentVisualizer : public FComponentVisualizer
{
public:
	//~ Begin FComponentVisualizer Interface
	virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;
	//~ End FComponentVisualizer Interface
};

UCLASS(hideCategories = (Trigger, PhysicsVolume), MinimalAPI)
class UCollisionTesterComponent : public UActorComponent
{
	GENERATED_BODY()
};

UCLASS()
class ACollisionTesterActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollisionTesterActor();

	virtual void PostInitProperties() override;

	UPROPERTY()
	TObjectPtr<UCollisionTesterComponent> CollisionTesterComponent;

	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTest> CollisionTest;

};

UCLASS(Abstract, EditInlineNew, CollapseCategories)
class UBaseCollisionTest : public UObject
{
public:
	GENERATED_BODY()
	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const PURE_VIRTUAL(UBaseCollisionTest::Draw, );
};

UCLASS(BlueprintType)
class UTraceCollsionTest : public UBaseCollisionTest
{
public:
	GENERATED_BODY()
	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const override;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	//Lenght of the trace
	UPROPERTY(EditInstanceOnly)
	float Length = 300;

};
