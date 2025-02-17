// Copyright Epic Games, Inc. All Rights Reserved.

#include "CollisionTesterEditor.h"

#include "CollisionTesterActor.h"
#include "Editor/UnrealEdEngine.h"

#include "UnrealEdGlobals.h"

#define LOCTEXT_NAMESPACE "FCollisionTesterEditorModule"

void FCollisionTesterEditorModule::StartupModule()
{
	if (GUnrealEd)
	{
		OnPostEngineInit();
	}
	else 
	{
		// wait for GEditor to be ready
		FCoreDelegates::OnPostEngineInit.AddRaw(this, &FCollisionTesterEditorModule::OnPostEngineInit);
	}
}

void FCollisionTesterEditorModule::OnPostEngineInit()
{
	if (GUnrealEd)
	{
		const FName CollisionTesterComponentName = UCollisionTesterComponent::StaticClass()->GetFName();
		GUnrealEd->RegisterComponentVisualizer(UCollisionTesterComponent::StaticClass()->GetFName(), MakeShareable(new FCollisionTesterComponentVisualizer));
		RegisteredComponentClassNames.Add(CollisionTesterComponentName);
	}
}

void FCollisionTesterEditorModule::ShutdownModule()
{
	// Unregister all component visualizers
	if (GEngine)
	{
		for (const FName ClassName : RegisteredComponentClassNames)
		{
			GUnrealEd->UnregisterComponentVisualizer(ClassName);
		}
	}
}
/*
const UMaterialInstanceDynamic* FCollisionTesterEditorModule::GetMaterial(const FColor& Color)
{
	if (MaterialMap.IsEmpty())
	{
		//Init at first use
		static const FString MaterialPath(TEXT("CollisionTesterEditor/Material/MAT_SphereColor.MAT_SphereColor"));
		BaseMaterial = LoadObject<UMaterial>(NULL, *MaterialPath, NULL, LOAD_None, NULL);

		UMaterialInstanceDynamic* RedMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, NULL);
		RedMaterial->SetVectorParameterValue(FName("Color"), FLinearColor::Red);
		RedMaterial->SetScalarParameterValue(FName("Desaturation"), 0.6f);
		MaterialMap.Emplace(FColor::Red, RedMaterial);

		UMaterialInstanceDynamic* GreenMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, NULL);
		GreenMaterial->SetVectorParameterValue(FName("Color"), FLinearColor::Green);
		GreenMaterial->SetScalarParameterValue(FName("Desaturation"), 0.6f);
		MaterialMap.Emplace(FColor::Green, GreenMaterial);

		UMaterialInstanceDynamic* BlueMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, NULL);
		BlueMaterial->SetVectorParameterValue(FName("Color"), FLinearColor::Blue);
		BlueMaterial->SetScalarParameterValue(FName("Desaturation"), 0.6f);
		MaterialMap.Emplace(FColor::Blue, BlueMaterial);
	}

	if (const UMaterialInstanceDynamic** Material = MaterialMap.Find(Color))
	{
		return *Material;
	}

	return nullptr;
}*/

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCollisionTesterEditorModule, CollisionTesterEditor)