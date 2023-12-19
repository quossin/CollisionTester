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

	/** End component to facilitate placing the end trace */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> EndComponent;

};

UCLASS(Abstract, EditInlineNew, CollapseCategories)
class UBaseCollisionTest : public UObject
{
public:
	GENERATED_BODY()
	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const PURE_VIRTUAL(UBaseCollisionTest::Draw, );

	void DrawHit(class FPrimitiveDrawInterface* PDI, const FHitResult& Hit, const class FMaterialRenderProxy* MaterialRenderProxy) const;

	FCollisionQueryParams GetQueryParams(AActor& Owner) const;

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
class UTraceCollsionTestByChannel : public UBaseCollisionTest
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

	UPROPERTY(EditInstanceOnly, Category = "Response")
	TEnumAsByte<ECollisionResponse> DefaultResponse = ECR_Block;

	UPROPERTY(EditInstanceOnly, Category = "Response")
	TArray<FCollisionTestResponsePair> ResponsePairs;
};

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
	virtual FCollisionObjectQueryParams GetCollisionObjectQueryParams() const;

	UPROPERTY(EditAnywhere, Category = "Collision")
	ECollisionTestByObjectMode CollisionTestByObjectMode = ECollisionTestByObjectMode::AllObjects;
};

UCLASS(EditInlineNew, CollapseCategories)
class UObjectTypeListCollisionTestByObjectMode : public UBaseCollisionTestByObjectMode
{
public:

	UObjectTypeListCollisionTestByObjectMode();

	GENERATED_BODY()
	virtual FCollisionObjectQueryParams GetCollisionObjectQueryParams() const;

	UPROPERTY(EditAnywhere, Category = "Collision")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
};

UCLASS(BlueprintType)
class UTraceCollsionTestByObjectType : public UBaseCollisionTest
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

	//Lenght of the trace
	UPROPERTY(EditInstanceOnly, Category = "Collision")
	float Length = 300;
};