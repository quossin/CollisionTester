// Copyright Juju & Seb. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "BaseCollisionTest.h"

#include "TraceCollisionTest.generated.h"


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
class UTraceCollisionTestByObjectType : public UBaseCollisionTest
{
public:
	GENERATED_BODY()

	virtual void PostInitProperties() override;
	virtual void Draw(ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const override;

	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTestByObjectMode> CollisionTestByObjectMode;

	//If true, it will also show overlap collision
	UPROPERTY(EditAnywhere, Category = "Collision")
	bool bMulti = true;

	UPROPERTY(EditDefaultsOnly, meta = (Bitmask, BitmaskEnum = EAnimalFlags))
	EFilterFlags FilterFlags;
};