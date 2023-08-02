// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class NvAR4U : ModuleRules
{

	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string ThirdPartyDirectory
	{
		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty")); }
	}

	public NvAR4U(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(ThirdPartyDirectory, "FacialExpressionLibrary/include"),
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
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
		PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyDirectory, "FacialExpressionLibrary/lib/Win64/FacialExpressionLibrary.lib"));
		// Delay-load the DLL, so we can load it from the right place first
		PublicDelayLoadDLLs.Add("FacialExpressionLibrary.dll");
		// Ensure that the DLL is staged along with the executable
		RuntimeDependencies.Add(Path.Combine(ThirdPartyDirectory, "FacialExpressionLibrary/lib/Win64/FacialExpressionLibrary.dll"));

	}
}
