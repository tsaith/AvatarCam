// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AvatarCam : ModuleRules
{
	public AvatarCam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "EnhancedInput",
		    "OpenCV", "OpenCVHelper" 
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "EnhancedInput",
		    "OpenCV", "OpenCVHelper", 
			//"OpenCVCustomized" 
		});
	}
}
