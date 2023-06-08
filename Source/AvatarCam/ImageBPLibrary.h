// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
    //static void PixelArrayToTexture(UTexture2D* &Texture, TArray<FColor> PixelArray, int Width, int Height);
    static UTexture2D* CreateTextureFromPixelArray(TArray<FColor> PixelArray, int Width, int Height);

};
