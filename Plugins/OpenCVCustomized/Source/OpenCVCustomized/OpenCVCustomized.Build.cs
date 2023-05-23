// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class OpenCVCustomized : ModuleRules
{
   private string ThirdPartyPath
   {
       get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
   }

	public OpenCVCustomized(ReadOnlyTargetRules Target) : base(Target)
	{

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

	    // Create OpenCV Path 
	    //string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
	    string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");

	    //Add Include path 
	    string IncludePath = Path.Combine(OpenCVPath, "Includes");
        PublicIncludePaths.AddRange(
			new string[] { IncludePath } );
		

		PrivateIncludePaths.AddRange(
			new string[] { } );
			
        // Add Library Path 
	    string LibPath = Path.Combine(OpenCVPath, "Libraries", "Win64");
        PublicSystemLibraryPaths.Add(LibPath);

		//Add Dynamic Libraries
		PublicDelayLoadDLLs.Add("opencv_world3410.dll");
        PublicDelayLoadDLLs.Add("opencv_ffmpeg3410_64.dll");
		//PublicDelayLoadDLLs.Add("opencv_world460.dll");
        //PublicDelayLoadDLLs.Add("opencv_videoio_ffmpeg460_64.dll");

		// Startard Module Dependencies
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "RHI", "RenderCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"CoreUObject", "Engine", "InputCore", "Slate", "SlateCore" });

	}
}
