// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FMocapLiveModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void* LoadLibrary(FString PluginDir, FString RelativePath);
	void FreeLibrary(void* Handle);

	void* LibMocapHandle;
	void* LibFacialExpressionHandle;
	void* LibMocapMpHandle;
};
