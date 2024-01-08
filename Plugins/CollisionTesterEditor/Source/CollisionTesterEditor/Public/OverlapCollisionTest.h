// Copyright Juju & Seb. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "CollisionTesterActor.h"
#include "CollisionTestShapes.h"
#include "BaseCollisionTest.h"

#include "OverlapCollisionTest.generated.h"

UCLASS(BlueprintType)
class UOverlapCollisionTestByChannel : public UBaseCollisionTest
{
public:
	GENERATED_BODY()

	virtual void PostInitProperties() override;
	virtual void Draw(class ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const override;

	//Channel to collide with
	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Pawn;

	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTestShape> Shape;

	UPROPERTY(EditInstanceOnly, Category = "Response")
	TEnumAsByte<ECollisionResponse> DefaultResponse = ECR_Block;

	UPROPERTY(EditInstanceOnly, Category = "Response")
	TArray<FCollisionTestResponsePair> ResponsePairs;
};

UCLASS(BlueprintType)
class UOverlapCollisionTestByObjectType : public UBaseCollisionTest
{
public:
	GENERATED_BODY()

	virtual void PostInitProperties() override;
	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const override;

	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTestByObjectMode> CollisionTestByObjectMode;

	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTestShape> Shape;

	UPROPERTY(EditDefaultsOnly, meta = (Bitmask, BitmaskEnum = EAnimalFlags))
	EFilterFlags FilterFlags;
};