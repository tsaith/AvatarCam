#include "MocapLive.h"

#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#include "LibMocap.h"

#define LOCTEXT_NAMESPACE "FMocapLiveModule"

void FMocapLiveModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("MocapLive")->GetBaseDir();

	// Add on the relative location of the third party dll and load it

	// The loading sequence is important
	LibDirectMLHandle = LoadLibrary(*BaseDir, TEXT("Binaries/ThirdParty/MocapLive/lib/Win64/DirectML.dll"));
    LibOnnxruntimeHandle = LoadLibrary(*BaseDir, TEXT("Binaries/ThirdParty/MocapLive/lib/Win64/onnxruntime.dll"));
	LibMediapipeHandle = LoadLibrary(*BaseDir, TEXT("Binaries/ThirdParty/MocapLive/lib/Win64/libmediapipe.dll"));
	LibMocapHandle = LoadLibrary(*BaseDir, TEXT("Binaries/ThirdParty/MocapLive/lib/Win64/LibMocap.dll"));

	if (!LibDirectMLHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load MocapLive: DirectML.dll."));
	}
	if (!LibOnnxruntimeHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load MocapLive: onnxruntime.dll."));
	}
	if (!LibMediapipeHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load MocapLive: libmediapipe.dll."));
	}
	if (!LibMocapHandle)
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load MocapLive: LibMocap.dll."));
	}

}

void FMocapLiveModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
 
	// Free the dll handle
	FreeLibrary(LibDirectMLHandle);
	FreeLibrary(LibOnnxruntimeHandle);
	FreeLibrary(LibMediapipeHandle);
	FreeLibrary(LibMocapHandle);

}

void* FMocapLiveModule::LoadLibrary(FString PluginDir, FString RelativePath)
{
	FString libPath = FPaths::Combine(*PluginDir, *RelativePath);
	void* handle = !libPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*libPath) : nullptr;

	return handle;
}

void FMocapLiveModule::FreeLibrary(void* Handle)
{
	if (Handle) {
	    FPlatformProcess::FreeDllHandle(Handle);
	    Handle = nullptr;
	}
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMocapLiveModule, MocapLive)
