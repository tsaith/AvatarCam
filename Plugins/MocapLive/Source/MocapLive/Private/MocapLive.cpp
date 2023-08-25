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
	FString LibPath;
	LibPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/MocapLive/lib/Win64/LibMocap.dll"));

	LibHandle = !LibPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibPath) : nullptr;

	if (LibHandle)
	{
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ThirdPartyLibraryError", "Failed to load MocapLive library."));
	}
}

void FMocapLiveModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(LibHandle);
	LibHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMocapLiveModule, MocapLive)
