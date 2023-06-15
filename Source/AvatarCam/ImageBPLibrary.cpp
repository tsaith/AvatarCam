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

void UImageBPLibrary::CreatePixelArrayFromTexture(UTexture2D* Texture2D, TArray<FColor> &PixelArray)
{

    TextureCompressionSettings OldCompressionSettings = Texture2D->CompressionSettings;
    TextureMipGenSettings OldMipGenSettings = Texture2D->MipGenSettings;
    bool OldSRGB = Texture2D->SRGB;

    Texture2D->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
    Texture2D->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
    Texture2D->SRGB = false;
    Texture2D->UpdateResource();

    FTexture2DMipMap& mipmap = Texture2D->PlatformData->Mips[0];
    uint8* Data = (uint8*)mipmap.BulkData.Lock(LOCK_READ_WRITE);
    if (Data == nullptr)
    {
        mipmap.BulkData.Unlock();
        Texture2D->UpdateResource();

        UE_LOG(LogTemp, Warning, TEXT("Error: empty data pointer of texture."));
    }

    int width = Texture2D->PlatformData->SizeX;
    int height = Texture2D->PlatformData->SizeY;
    for (int32 y = 0; y < height; y++)
    {
        for (int32 x = 0; x < width; x++)
        {
            FColor pixel;
            pixel.B = Data[(y * width + x) * 4 + 0];//B 0 - 255
            pixel.G = Data[(y * width + x) * 4 + 1];//G
            pixel.R = Data[(y * width + x) * 4 + 2];//R
            pixel.A = Data[(y * width + x) * 4 + 3];//A 
            PixelArray.Add(pixel);
        }
    }

}

bool UImageBPLibrary::ExportImage(UTexture2D* Texture2D, const FString& Path)
{

    TextureCompressionSettings OldCompressionSettings = Texture2D->CompressionSettings;
    TextureMipGenSettings OldMipGenSettings = Texture2D->MipGenSettings;
    bool OldSRGB = Texture2D->SRGB;

    Texture2D->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
    Texture2D->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
    Texture2D->SRGB = false;
    Texture2D->UpdateResource();

    FTexture2DMipMap& mipmap = Texture2D->PlatformData->Mips[0];
    uint8* Data = (uint8*)mipmap.BulkData.Lock(LOCK_READ_WRITE);
    if (Data == nullptr)
    {
        mipmap.BulkData.Unlock(); 
        Texture2D->UpdateResource();
        return false;
    }

    int width = Texture2D->PlatformData->SizeX;
    int height = Texture2D->PlatformData->SizeY;
    TArray<FColor> nColors;

    for (int32 y = 0; y < height; y++)
    {
        for (int32 x = 0; x < width; x++)
        {
            FColor bColor;
            bColor.B = Data[(y * width + x) * 4 + 0];//B 0 - 255
            bColor.G = Data[(y * width + x) * 4 + 1];//G
            bColor.R = Data[(y * width + x) * 4 + 2];//R
            bColor.A = Data[(y * width + x) * 4 + 3];//A 
            nColors.Add(bColor);
        }
    }
    mipmap.BulkData.Unlock();

    // return old parameters
    Texture2D->CompressionSettings = OldCompressionSettings;
    Texture2D->MipGenSettings = OldMipGenSettings;
    Texture2D->SRGB = OldSRGB;

    Texture2D->UpdateResource();

    TArray<uint8> ImgData;
    FImageUtils::CompressImageArray(width, height, nColors, ImgData);
    return FFileHelper::SaveArrayToFile(ImgData, *Path);

}
