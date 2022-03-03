// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyUE427Study02 : ModuleRules
{
	public MyUE427Study02(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}