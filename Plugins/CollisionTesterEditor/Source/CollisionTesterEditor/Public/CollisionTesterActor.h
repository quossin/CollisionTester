// Fill out your copyright noTtice in the Description page of Project Settings.

#pragma once

#include "CollisionShape.h"
#include "ComponentVisualizer.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

#include "CollisionTesterActor.generated.h"

class ActorComponent;
class UBaseCollisionTestShape;

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

UCLASS(Abstract, EditInlineNew, CollapseCategories)
class UBaseCollisionTest : public UObject
{
public:
	GENERATED_BODY()
	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const PURE_VIRTUAL(UBaseCollisionTest::Draw, );

	void DrawHit(class FPrimitiveDrawInterface* PDI, const FHitResult& Hit, const class FMaterialRenderProxy* MaterialRenderProxy) const;

	FCollisionQueryParams GetQueryParams(const AActor& Owner) const;

	/** Whether we should trace against complex collision */
	UPROPERTY(EditInstanceOnly, Category = "Params")
	bool bTraceComplex = false;

	/** Whether we want to find out initial overlap or not. If true, it will return if this was initial overlap. */
	UPROPERTY(EditInstanceOnly, Category = "Params")
	bool bFindInitialOverlaps = true;

	/** Whether to ignore blocking results. */
	UPROPERTY(EditInstanceOnly, Category = "Params")
	bool bIgnoreBlocks = false;

	/** Whether to ignore touch/overlap results. */
	UPROPERTY(EditInstanceOnly, Category = "Params")
	bool bIgnoreTouches = false;

	/** Whether to skip narrow phase checks (only for overlaps). */
	UPROPERTY(EditInstanceOnly, Category = "Params")
	bool bSkipNarrowPhase = false;

	/** Whether to ignore traces to the cluster union and trace against its children instead. */
	UPROPERTY(EditInstanceOnly, Category = "Params")
	bool bTraceIntoSubComponents = false;
};

USTRUCT(BlueprintType)
struct FCollisionTestResponsePair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_WorldStatic;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionResponse> Response = ECR_Block;
};

UCLASS(BlueprintType)
class UTraceCollisionTestByChannel : public UBaseCollisionTest
{
public:
	GENERATED_BODY()
	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const override;

	//Channel to collide with
	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	//If true, it will also show overlap collision
	UPROPERTY(EditAnywhere, Category = "Collision")
	bool bMulti = true;

	//Default response channel to check with the trace
	UPROPERTY(EditInstanceOnly, Category = "Response")
	TEnumAsByte<ECollisionResponse> DefaultResponse = ECR_Block;

	//Specific collision channel and it's associated response
	UPROPERTY(EditInstanceOnly, Category = "Response")
	TArray<FCollisionTestResponsePair> ResponsePairs;
};

UCLASS(BlueprintType)
class USweepCollisionTestByChannel : public UTraceCollisionTestByChannel
{
public:
	GENERATED_BODY()

	virtual void PostInitProperties() override;

	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, FPrimitiveDrawInterface* PDI) const override;
	virtual void DrawShapes(ACollisionTesterActor* CollisionTesterOwner, const FVector& ShapeLocation,
		FPrimitiveDrawInterface* PDI, const FLinearColor& ColorToUse, FCollisionShape& UsedShape) const;

	// Instanced shape data to use for the trace
	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTestShape> Shape;
};

/* By Object Trace */

UCLASS(Abstract, EditInlineNew, CollapseCategories)
class UBaseCollisionTestByObjectMode : public UObject
{
public:
	GENERATED_BODY()
	virtual FCollisionObjectQueryParams GetCollisionObjectQueryParams() const PURE_VIRTUAL(UBaseCollisionTestByObjectMode::GetCollisionObjectQueryParams, return FCollisionObjectQueryParams(););
};

UENUM()
enum class ECollisionTestByObjectMode : uint8
{
	AllObjects,
	AllStaticObjects,
	AllDynamicObjects
};

UCLASS(EditInlineNew, CollapseCategories)
class UAllTypeListCollisionTestByObjectMode : public UBaseCollisionTestByObjectMode
{
public:
	GENERATED_BODY()
	virtual FCollisionObjectQueryParams GetCollisionObjectQueryParams() const override;

	UPROPERTY(EditAnywhere, Category = "Collision")
	ECollisionTestByObjectMode CollisionTestByObjectMode = ECollisionTestByObjectMode::AllObjects;
};

UCLASS(EditInlineNew, CollapseCategories)
class UObjectTypeListCollisionTestByObjectMode : public UBaseCollisionTestByObjectMode
{
public:

	UObjectTypeListCollisionTestByObjectMode();

	GENERATED_BODY()
	virtual FCollisionObjectQueryParams GetCollisionObjectQueryParams() const override;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
};

UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EFilterFlags : uint8
{
	Flag1 = 1 << 0,
	Flag2 = 2 << 1,
	Flag3 = 3 << 2,
	Flag4 = 4 << 3,
	Flag5 = 5 << 4,
	Flag6 = 6 << 5,
};

ENUM_CLASS_FLAGS(EFilterFlags)

UCLASS(BlueprintType)
class UTraceCollisionTestByObjectType : public UBaseCollisionTest
{
public:
	GENERATED_BODY()

	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const override;

	virtual void PostInitProperties() override;

	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTestByObjectMode> CollisionTestByObjectMode;

	//If true, it will also show overlap collision
	UPROPERTY(EditAnywhere, Category = "Collision")
	bool bMulti = true;

	UPROPERTY(EditDefaultsOnly, meta = (Bitmask, BitmaskEnum = EAnimalFlags))
	EFilterFlags FilterFlags;
};