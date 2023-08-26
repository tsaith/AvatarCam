// Copyright Epic Games, Inc. All Rights Reserved.

//using Tools.DotNETCommon;
using System;
using System.IO;
using UnrealBuildTool;

public class AvatarCam : ModuleRules
{
	public AvatarCam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "EnhancedInput",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "EnhancedInput",
			"ImageWrapper", "RenderCore",
			"OpenCV", "OpenCVHelper",
			"VRM4U", "MocapLive"
		});

	}
}
