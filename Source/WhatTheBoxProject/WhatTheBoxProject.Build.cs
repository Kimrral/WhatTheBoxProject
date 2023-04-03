// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WhatTheBoxProject : ModuleRules
{
	public WhatTheBoxProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", "OnlineSubsystem", "Slate", "SlateCore" });

//         PrivateDependencyModuleNames.AddRange(new string[] { });
// 
//         PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
