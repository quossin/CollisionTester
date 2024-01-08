// Copyright Juju & Seb. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CollisionTesterEditorTarget : TargetRules
{
	public CollisionTesterEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("CollisionTester");
	}
}
