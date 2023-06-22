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
			"VideoReader",
		});

        // Load libmocap_mp.dll
        string MocapMpDLL = "libmocap_mp.dll";
		string ProjectDirectory = Path.Combine(ModuleDirectory, "..\\..\\");
		string MocapMpDLLPath = Path.Combine(ProjectDirectory, "Libs", MocapMpDLL);
		//Console.WriteLine("DllPath: {0}", DLLPath);

		PublicDelayLoadDLLs.Add(MocapMpDLL);
        RuntimeDependencies.Add(MocapMpDLLPath);

	}
}
