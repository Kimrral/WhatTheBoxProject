// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WhatTheBoxProject : ModuleRules
{
	public WhatTheBoxProject(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivateDependencyModuleNames.AddRange(new string[] { "AdvancedWidgets" });
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "OnlineSubsystemSteam", "OnlineSubsystem", "VirtualCamera" });
	}
}
