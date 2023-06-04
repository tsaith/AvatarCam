using System.IO;
using UnrealBuildTool;

public class MocapMpLibrary : ModuleRules {
  public MocapMpLibrary(ReadOnlyTargetRules Target) : base(Target) {
    Type = ModuleType.External;

    if (Target.Platform == UnrealTargetPlatform.Win64) {
      string DLLName = "libmocap_mp.dll";
      string DLLPath = Path.Combine(ModuleDirectory, "Win64", DLLName);
	  PublicDelayLoadDLLs.Add(DLLName);
      RuntimeDependencies.Add(DLLPath);
    }
  }
}