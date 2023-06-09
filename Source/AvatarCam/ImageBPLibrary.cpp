// Fill out your copyright notice in the Description page of Project Settings.


#include "ImageBPLibrary.h"


UTexture2D* UImageBPLibrary::CreateImageTexture(int Width, int Height)
{
    UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);

    // Ensure all settings are the way we want them
    Texture->MipGenSettings = TMGS_NoMipmaps;
    Texture->SRGB = false;
    Texture->UpdateResource();

    return Texture;
}

UTexture2D* UImageBPLibrary::CreateTextureFromPixelArray(TArray<FColor> PixelArray, int Width, int Height)
{

    check(PixelArray.Num() == Width * Height);

    UTexture2D* Texture = CreateImageTexture(Width, Height);

    // Lock the texture so it can be modified
    void* textureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);

    // Copy the pixels to the texture
    FMemory::Memcpy(textureData, PixelArray.GetData(), PixelArray.Num()*sizeof(FColor));

    // Unlock the texture
    Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

    // Update the texture and mark it as ready for use
    Texture->UpdateResource();

    return Texture;
}

