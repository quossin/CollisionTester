// Copyright Juju & Seb. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class COLLISIONTESTEREDITOR_API FCollisionTesterEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void OnPostEngineInit();

	
	//const UMaterialInstanceDynamic* GetMaterial(const FColor& Color);

private:
	TArray<FName> RegisteredComponentClassNames;
	/*
	UPROPERTY(Transient)
	TObjectPtr<class UMaterial> BaseMaterial;

	UPROPERTY(Transient)
	TMap<FColor, const UMaterialInstanceDynamic*> MaterialMap;
	*/
	
};
