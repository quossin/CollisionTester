// Copyright Juju & Seb. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "CollisionQueryParams.h"
#include "Engine/Engine.h"

#include "BaseCollisionTest.generated.h"

USTRUCT(BlueprintType)
struct FCollisionTestResponsePair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_WorldStatic;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionResponse> Response = ECR_Block;
};

UCLASS(Abstract, EditInlineNew, CollapseCategories)
class UBaseCollisionTest : public UObject
{
public:
	GENERATED_BODY()
	virtual void Draw(class ACollisionTesterActor* CollisionTesterOwner, class FPrimitiveDrawInterface* PDI) const PURE_VIRTUAL(UBaseCollisionTest::Draw, );

	void DrawHit(class FPrimitiveDrawInterface* PDI, const FHitResult& Hit, const FColor& Color) const;

	void DrawHit(class FPrimitiveDrawInterface* PDI, const FHitResult& Hit, const class FMaterialRenderProxy* MaterialRenderProxy) const;

	FCollisionQueryParams GetQueryParams(const AActor& Owner) const;

	template<class HITRESULT_CLASS>
	void PrintHitInfo(const HITRESULT_CLASS& Hit, int32 Index = 0) const
	{
		const FColor TextColor = Hit.bBlockingHit ? FColor::Red : FColor::Blue;

		const FString ActorName = Hit.GetActor() ? Hit.GetActor()->GetName() : FString(TEXT("UNKNOWN"));
		const FString ComponentName = Hit.GetComponent() ? Hit.GetComponent()->GetName() : FString(TEXT("UNKNOWN"));

		const FString Text = FString::Format(TEXT("CollisionTest Hit: {0} ({1} )"),
			{
				*ActorName
				, *ComponentName
			}
		);

		GEngine->AddOnScreenDebugMessage(reinterpret_cast<uint64>(this) + Index, 0.1f, TextColor, *Text, false);
	}

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
