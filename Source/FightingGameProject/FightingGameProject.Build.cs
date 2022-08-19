// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FightingGameProject : ModuleRules
{
	public FightingGameProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
