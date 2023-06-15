// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ImageUtils.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ImageBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AVATARCAM_API UImageBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintPure, Category = "ImageBPLibrary")
        static UTexture2D* CreateImageTexture(int Width, int Height);

    UFUNCTION(BlueprintPure, Category = "ImageBPLibrary")
        static UTexture2D* CreateTextureFromPixelArray(TArray<FColor> PixelArray, int Width, int Height);

    UFUNCTION(BlueprintPure, Category = "ImageBPLibrary")
        static void CreatePixelArrayFromTexture(UTexture2D* Texture2D, TArray<FColor>& PixelArray);

	UFUNCTION(BlueprintCallable, Category = "ImageBPLibrary")
        static bool ExportImage(UTexture2D* Texture2D, const FString& Path);

};
