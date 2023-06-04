// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "VideoReaderActor.h"

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FVideoReaderModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
