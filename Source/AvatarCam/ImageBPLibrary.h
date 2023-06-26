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

    /*
    UFUNCTION(BlueprintPure, Category = "ImageBPLibrary")
        static void ConvertTextureToPixelArray(UTexture2D* &Texture, TArray<FColor>& PixelArray);

    UFUNCTION(BlueprintPure, Category = "ImageBPLibrary")
        static void ConvertPixelArrayToTexture(TArray<FColor> &PixelArray, UTexture2D* &Texture, int Width, int Height);

	UFUNCTION(BlueprintCallable, Category = "ImageBPLibrary")
        static bool ExportImage(UTexture2D* Texture2D, const FString& Filepath);
    */

};
