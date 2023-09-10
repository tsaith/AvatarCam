// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class MocapLive : ModuleRules
{

	private string ThirdPartyDirectory
	{
		get { return Path.GetFullPath(Path.Combine(PluginDirectory, "Binaries", "ThirdParty")); }
	}

	private string LibRootDirectory
	{
		get { return Path.GetFullPath(Path.Combine(ThirdPartyDirectory, "MocapLive")); }
	}

	public MocapLive(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(LibRootDirectory, "include"),
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Projects",
				"OpenCV", "OpenCVHelper",
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);


		// Add the import library
		PublicAdditionalLibraries.Add(Path.Combine(LibRootDirectory, "lib/Win64/LibMocap.lib"));

		// Delay-load the DLL, so we can load it from the right place first
		PublicDelayLoadDLLs.Add("LibMocap.dll");
		PublicDelayLoadDLLs.Add("LibFacialExpression.dll");
		PublicDelayLoadDLLs.Add("libmediapipe.dll");
		PublicDelayLoadDLLs.Add("onnxruntime.dll");
		PublicDelayLoadDLLs.Add("DirectML.dll");

		// Ensure that the DLL is staged along with the executable
		RuntimeDependencies.Add(Path.Combine(LibRootDirectory, "lib/Win64/LibMocap.dll"));
		RuntimeDependencies.Add(Path.Combine(LibRootDirectory, "lib/Win64/LibFacialExpression.dll"));
		RuntimeDependencies.Add(Path.Combine(LibRootDirectory, "lib/Win64/libmediapipe.dll"));
		RuntimeDependencies.Add(Path.Combine(LibRootDirectory, "lib/Win64/onnxruntime.dll"));
		RuntimeDependencies.Add(Path.Combine(LibRootDirectory, "lib/Win64/DirectML.dll"));

	}
}
