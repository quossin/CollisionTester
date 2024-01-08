// Copyright Juju & Seb. All Rights Reserved.

#pragma once

#include "CollisionShape.h"
#include "ComponentVisualizer.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

#include "CollisionTesterActor.generated.h"

class ActorComponent;
class UBaseCollisionTestShape;
class UBaseCollisionTest;

/* Blueprint available enum for collision shape used with the collision tester */
UENUM(BlueprintType)
enum ECollisionTesterShapeType : uint8
{
	Line = ECollisionShape::Line UMETA(Hidden), // Don't show line shape, it's useless
	Box = ECollisionShape::Type::Box,
	Sphere = ECollisionShape::Type::Sphere,
	Capsule = ECollisionShape::Type::Capsule,
};

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

// Editor actor than can be placed in a level to quickly do trace testing
UCLASS(hideCategories = (Rendering, Replication, Collision, HLOD, Physics, Networking, Input, Actor, LevelInstance, Cooking))
class ACollisionTesterActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollisionTesterActor();

	virtual void PostInitProperties() override;

	UPROPERTY()
	TObjectPtr<UCollisionTesterComponent> CollisionTesterComponent;

	//Type of collision test to do
	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTest> CollisionTest;

	/** Normal editor sprite. */
	UPROPERTY()
	TObjectPtr<class UBillboardComponent> Sprite;

	UFUNCTION(BlueprintCallable)
	FTransform GetTraceEndTransform() const;

private:
	/* End transform of the trace, take notes that the scale will not be used */
	UPROPERTY(EditAnywhere, meta=(MakeEditWidget, AllowPrivateAccess))
	FTransform EndOfTrace;

};
