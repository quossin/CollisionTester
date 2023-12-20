// Fill out your copyright noTtice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CollisionTesterActor.h"
#include "CollisionTestShapes.h"

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
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	UPROPERTY(EditInstanceOnly, Instanced, NoClear, meta = (NoResetToDefault))
	TObjectPtr<UBaseCollisionTestShape> Shape;

	//If true, it will also show overlap collision
	UPROPERTY(EditAnywhere, Category = "Collision")
	bool bMulti = true;

	UPROPERTY(EditInstanceOnly, Category = "Response")
	TEnumAsByte<ECollisionResponse> DefaultResponse = ECR_Block;

	UPROPERTY(EditInstanceOnly, Category = "Response")
	TArray<FCollisionTestResponsePair> ResponsePairs;
};