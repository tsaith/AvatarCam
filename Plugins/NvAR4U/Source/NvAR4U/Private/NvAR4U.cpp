#include "NvAR4U.h"

//#include "Core.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/MessageDialog.h"

#define LOCTEXT_NAMESPACE "FNvAR4UModule"

void FNvAR4UModule::StartupModule()
{
    // Get the base directory of this plugin
    FString baseDir = IPluginManager::Get().FindPlugin("NvAR4U")->GetBaseDir();
    FString libPath = FPaths::Combine(*baseDir, TEXT("Source/ThirdParty/FacialExpressionLibrary/lib/Win64/FacialExpressionLibrary.dll"));
    mLibHandle = !libPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*libPath) : nullptr;

    if (mLibHandle) {
         // Some code that will be executed if dll was found
		UE_LOG(LogTemp, Display, TEXT("FacialExpressionLibrary.dll is loaded."));
    }
    else
    {
        FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Error: ", "Failed to load FacialExpressionLibrary.dll"));
    }

}

void FNvAR4UModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    if (mLibHandle) {
        FPlatformProcess::FreeDllHandle(mLibHandle);
        mLibHandle = nullptr;
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNvAR4UModule, NvAR4U)