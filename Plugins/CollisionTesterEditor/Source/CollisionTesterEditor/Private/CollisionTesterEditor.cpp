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

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCollisionTesterEditorModule, CollisionTesterEditor)