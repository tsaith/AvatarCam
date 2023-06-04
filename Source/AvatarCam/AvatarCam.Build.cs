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
			//"MocapMp",
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "EnhancedInput",
		    "OpenCV", "OpenCVHelper", 
			//"MocapMp",
		});

        // Load libmocap_mp.dll
        string DLLName = "libmocap_mp.dll";
		string ProjectDirectory = Path.Combine(ModuleDirectory, "..\\..\\");
		string DLLPath = Path.Combine(ProjectDirectory, "Libs", DLLName);
		//Console.WriteLine("DllPath: {0}", DLLPath);

		PublicDelayLoadDLLs.Add(DLLName);
        RuntimeDependencies.Add(DLLPath);

	}
}
