// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CollisionTesterEditor/Public/CollisionTesterActor.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCollisionTesterActor() {}
// Cross Module References
	COLLISIONTESTEREDITOR_API UClass* Z_Construct_UClass_ACollisionTesterActor();
	COLLISIONTESTEREDITOR_API UClass* Z_Construct_UClass_ACollisionTesterActor_NoRegister();
	COLLISIONTESTEREDITOR_API UClass* Z_Construct_UClass_UBaseCollisionTest();
	COLLISIONTESTEREDITOR_API UClass* Z_Construct_UClass_UBaseCollisionTest_NoRegister();
	COLLISIONTESTEREDITOR_API UClass* Z_Construct_UClass_UCollisionTesterComponent();
	COLLISIONTESTEREDITOR_API UClass* Z_Construct_UClass_UCollisionTesterComponent_NoRegister();
	COLLISIONTESTEREDITOR_API UClass* Z_Construct_UClass_UTraceCollsionTest();
	COLLISIONTESTEREDITOR_API UClass* Z_Construct_UClass_UTraceCollsionTest_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API UEnum* Z_Construct_UEnum_Engine_ECollisionChannel();
	UPackage* Z_Construct_UPackage__Script_CollisionTesterEditor();
// End Cross Module References
	void UCollisionTesterComponent::StaticRegisterNativesUCollisionTesterComponent()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCollisionTesterComponent);
	UClass* Z_Construct_UClass_UCollisionTesterComponent_NoRegister()
	{
		return UCollisionTesterComponent::StaticClass();
	}
	struct Z_Construct_UClass_UCollisionTesterComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCollisionTesterComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_CollisionTesterEditor,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCollisionTesterComponent_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCollisionTesterComponent_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "CollisionTesterActor.h" },
		{ "ModuleRelativePath", "Public/CollisionTesterActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCollisionTesterComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCollisionTesterComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCollisionTesterComponent_Statics::ClassParams = {
		&UCollisionTesterComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00A800A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCollisionTesterComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UCollisionTesterComponent_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UCollisionTesterComponent()
	{
		if (!Z_Registration_Info_UClass_UCollisionTesterComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCollisionTesterComponent.OuterSingleton, Z_Construct_UClass_UCollisionTesterComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCollisionTesterComponent.OuterSingleton;
	}
	template<> COLLISIONTESTEREDITOR_API UClass* StaticClass<UCollisionTesterComponent>()
	{
		return UCollisionTesterComponent::StaticClass();
	}
	UCollisionTesterComponent::UCollisionTesterComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCollisionTesterComponent);
	UCollisionTesterComponent::~UCollisionTesterComponent() {}
	void ACollisionTesterActor::StaticRegisterNativesACollisionTesterActor()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ACollisionTesterActor);
	UClass* Z_Construct_UClass_ACollisionTesterActor_NoRegister()
	{
		return ACollisionTesterActor::StaticClass();
	}
	struct Z_Construct_UClass_ACollisionTesterActor_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CollisionTesterComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_CollisionTesterComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CollisionTest_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_CollisionTest;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ACollisionTesterActor_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_CollisionTesterEditor,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACollisionTesterActor_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACollisionTesterActor_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CollisionTesterActor.h" },
		{ "ModuleRelativePath", "Public/CollisionTesterActor.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTesterComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/CollisionTesterActor.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTesterComponent = { "CollisionTesterComponent", nullptr, (EPropertyFlags)0x0014000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACollisionTesterActor, CollisionTesterComponent), Z_Construct_UClass_UCollisionTesterComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTesterComponent_MetaData), Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTesterComponent_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTest_MetaData[] = {
		{ "Category", "CollisionTesterActor" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/CollisionTesterActor.h" },
		{ "NoResetToDefault", "" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTest = { "CollisionTest", nullptr, (EPropertyFlags)0x0016000002080809, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ACollisionTesterActor, CollisionTest), Z_Construct_UClass_UBaseCollisionTest_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTest_MetaData), Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTest_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ACollisionTesterActor_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTesterComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ACollisionTesterActor_Statics::NewProp_CollisionTest,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ACollisionTesterActor_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACollisionTesterActor>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ACollisionTesterActor_Statics::ClassParams = {
		&ACollisionTesterActor::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ACollisionTesterActor_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ACollisionTesterActor_Statics::PropPointers),
		0,
		0x008000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ACollisionTesterActor_Statics::Class_MetaDataParams), Z_Construct_UClass_ACollisionTesterActor_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ACollisionTesterActor_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ACollisionTesterActor()
	{
		if (!Z_Registration_Info_UClass_ACollisionTesterActor.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACollisionTesterActor.OuterSingleton, Z_Construct_UClass_ACollisionTesterActor_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ACollisionTesterActor.OuterSingleton;
	}
	template<> COLLISIONTESTEREDITOR_API UClass* StaticClass<ACollisionTesterActor>()
	{
		return ACollisionTesterActor::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ACollisionTesterActor);
	ACollisionTesterActor::~ACollisionTesterActor() {}
	void UBaseCollisionTest::StaticRegisterNativesUBaseCollisionTest()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBaseCollisionTest);
	UClass* Z_Construct_UClass_UBaseCollisionTest_NoRegister()
	{
		return UBaseCollisionTest::StaticClass();
	}
	struct Z_Construct_UClass_UBaseCollisionTest_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBaseCollisionTest_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CollisionTesterEditor,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseCollisionTest_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBaseCollisionTest_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "CollisionTesterActor.h" },
		{ "ModuleRelativePath", "Public/CollisionTesterActor.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBaseCollisionTest_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBaseCollisionTest>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBaseCollisionTest_Statics::ClassParams = {
		&UBaseCollisionTest::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000030A1u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBaseCollisionTest_Statics::Class_MetaDataParams), Z_Construct_UClass_UBaseCollisionTest_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UBaseCollisionTest()
	{
		if (!Z_Registration_Info_UClass_UBaseCollisionTest.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBaseCollisionTest.OuterSingleton, Z_Construct_UClass_UBaseCollisionTest_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UBaseCollisionTest.OuterSingleton;
	}
	template<> COLLISIONTESTEREDITOR_API UClass* StaticClass<UBaseCollisionTest>()
	{
		return UBaseCollisionTest::StaticClass();
	}
	UBaseCollisionTest::UBaseCollisionTest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBaseCollisionTest);
	UBaseCollisionTest::~UBaseCollisionTest() {}
	void UTraceCollsionTest::StaticRegisterNativesUTraceCollsionTest()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTraceCollsionTest);
	UClass* Z_Construct_UClass_UTraceCollsionTest_NoRegister()
	{
		return UTraceCollsionTest::StaticClass();
	}
	struct Z_Construct_UClass_UTraceCollsionTest_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TraceChannelProperty_MetaData[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_TraceChannelProperty;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Length_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_Length;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTraceCollsionTest_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBaseCollisionTest,
		(UObject* (*)())Z_Construct_UPackage__Script_CollisionTesterEditor,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTraceCollsionTest_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTraceCollsionTest_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "CollisionTesterActor.h" },
		{ "ModuleRelativePath", "Public/CollisionTesterActor.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_TraceChannelProperty_MetaData[] = {
		{ "Category", "Collision" },
		{ "ModuleRelativePath", "Public/CollisionTesterActor.h" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_TraceChannelProperty = { "TraceChannelProperty", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTraceCollsionTest, TraceChannelProperty), Z_Construct_UEnum_Engine_ECollisionChannel, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_TraceChannelProperty_MetaData), Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_TraceChannelProperty_MetaData) }; // 1822723181
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_Length_MetaData[] = {
		{ "Category", "TraceCollsionTest" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//Lenght of the trace\n" },
#endif
		{ "ModuleRelativePath", "Public/CollisionTesterActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Lenght of the trace" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_Length = { "Length", nullptr, (EPropertyFlags)0x0010000000000801, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UTraceCollsionTest, Length), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_Length_MetaData), Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_Length_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UTraceCollsionTest_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_TraceChannelProperty,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UTraceCollsionTest_Statics::NewProp_Length,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTraceCollsionTest_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UTraceCollsionTest>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UTraceCollsionTest_Statics::ClassParams = {
		&UTraceCollsionTest::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UTraceCollsionTest_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UTraceCollsionTest_Statics::PropPointers),
		0,
		0x000030A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTraceCollsionTest_Statics::Class_MetaDataParams), Z_Construct_UClass_UTraceCollsionTest_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTraceCollsionTest_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UTraceCollsionTest()
	{
		if (!Z_Registration_Info_UClass_UTraceCollsionTest.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTraceCollsionTest.OuterSingleton, Z_Construct_UClass_UTraceCollsionTest_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UTraceCollsionTest.OuterSingleton;
	}
	template<> COLLISIONTESTEREDITOR_API UClass* StaticClass<UTraceCollsionTest>()
	{
		return UTraceCollsionTest::StaticClass();
	}
	UTraceCollsionTest::UTraceCollsionTest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTraceCollsionTest);
	UTraceCollsionTest::~UTraceCollsionTest() {}
	struct Z_CompiledInDeferFile_FID_CollisionTester_Plugins_CollisionTesterEditor_Source_CollisionTesterEditor_Public_CollisionTesterActor_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_CollisionTester_Plugins_CollisionTesterEditor_Source_CollisionTesterEditor_Public_CollisionTesterActor_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCollisionTesterComponent, UCollisionTesterComponent::StaticClass, TEXT("UCollisionTesterComponent"), &Z_Registration_Info_UClass_UCollisionTesterComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCollisionTesterComponent), 615226954U) },
		{ Z_Construct_UClass_ACollisionTesterActor, ACollisionTesterActor::StaticClass, TEXT("ACollisionTesterActor"), &Z_Registration_Info_UClass_ACollisionTesterActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACollisionTesterActor), 2038170234U) },
		{ Z_Construct_UClass_UBaseCollisionTest, UBaseCollisionTest::StaticClass, TEXT("UBaseCollisionTest"), &Z_Registration_Info_UClass_UBaseCollisionTest, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBaseCollisionTest), 2469419654U) },
		{ Z_Construct_UClass_UTraceCollsionTest, UTraceCollsionTest::StaticClass, TEXT("UTraceCollsionTest"), &Z_Registration_Info_UClass_UTraceCollsionTest, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTraceCollsionTest), 1936382550U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_CollisionTester_Plugins_CollisionTesterEditor_Source_CollisionTesterEditor_Public_CollisionTesterActor_h_2251618507(TEXT("/Script/CollisionTesterEditor"),
		Z_CompiledInDeferFile_FID_CollisionTester_Plugins_CollisionTesterEditor_Source_CollisionTesterEditor_Public_CollisionTesterActor_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_CollisionTester_Plugins_CollisionTesterEditor_Source_CollisionTesterEditor_Public_CollisionTesterActor_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
