// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoReader.h"

// Sets default values
AVideoReader::AVideoReader()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVideoReader::BeginPlay()
{
	Super::BeginPlay();
	
    mImage = cv::Mat(ImageHeight, ImageWidth, CV_8UC3, cv::Scalar(0, 0, 0));

    // Initialize data array
    mData.Init(FColor(0, 0, 0, 255), ImageWidth * ImageHeight);

    if (AsVideoReader) {
    
    	AsCameraReader = false;
    	AsImageReader = false;
    
    	mVideoPath = FPaths::Combine(mVideoDir, VideoFilename);
        if (FPaths::FileExists(mVideoPath)) {
            mVideoReader.Open(mVideoPath);
            UE_LOG(LogTemp, Warning, TEXT("Open video."));
        }
        else 
        {
            UE_LOG(LogTemp, Error, TEXT("Error: Video is not found."));
        
        }

    }
    else 
    {
        if (AsCameraReader) {
            AsImageReader = false;

            int cameraID = 0;
            mVideoReader.Open(cameraID, ImageWidth, ImageHeight);
            UE_LOG(LogTemp, Warning, TEXT("Open camera."));
        }
        else
        {

            FString imagePath = FPaths::Combine(mImageDir, ImageFilename);

            if (FPaths::FileExists(imagePath)) {

                cv::String path = TCHAR_TO_ANSI(*imagePath);
                cv::Mat imageRaw = cv::imread(path);
                cv::resize(imageRaw, mImage, cv::Size(ImageWidth, ImageHeight));
            }
    	    else 
            {
    		     UE_LOG(LogTemp, Error, TEXT("Error: Target image can't be found."));
    	     }

        }
    
    }

}

// Called every frame
void AVideoReader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	cv::Mat frame;
	if (AsVideoReader || AsCameraReader) {

        mVideoReader.Read(frame);
        cv::resize(frame, mImage, cv::Size(ImageWidth, ImageHeight));

	}
    
    UpdateImageData();
    UpdateImageTexture();

}

void AVideoReader::UpdateImageData()
{

	if (mImage.data)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			for (int x = 0; x < ImageWidth; x++)
			{
				int i = x + (y * ImageWidth);
				mData[i].B = mImage.data[i * 3 + 0];
				mData[i].G = mImage.data[i * 3 + 1];
				mData[i].R = mImage.data[i * 3 + 2];
                // Alpha is as 255;
			}
		}

	}

}

void AVideoReader::UpdateImageTexture()
{

    //mImageTexture = CreateTextureFromPixelArray(mData, mImage.cols, mImage.rows);

    cv::Mat_<cv::Vec4b> tmpMat;
    createAlphaImage(mImage, tmpMat);
    mImageTexture = FOpenCVHelper::TextureFromCvMat(tmpMat);

    FString filepath = "C:\\Users\\andrew\\projects\\AvatarCam\\Outputs\\diag.png";
    ExportImage(mImageTexture, filepath);
}


void AVideoReader::GetData(TArray<FColor>& Data) {
	Data = mData;
}

void AVideoReader::GetImageTexture(UTexture2D* &ImageTexture)
{
	ImageTexture = mImageTexture;
}

UTexture2D* AVideoReader::CreateTextureFromPixelArray(TArray<FColor> &Data, int Width, int Height)
{
    UTexture2D*Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
    if (!Texture)
    {
        return nullptr;
    }
 
    FTexture2DMipMap& Mip = Texture->PlatformData->Mips[0];
    void* pData = Mip.BulkData.Lock(LOCK_READ_WRITE);

    FMemory::Memcpy(pData, Data.GetData(), Width * Height * 4);
    Mip.BulkData.Unlock();
    Texture->UpdateResource();

    return Texture;
}

/*
UTexture2D* AVideoReader::CreateTextureFromPixelArray(TArray<FColor>& Data, int Width, int Height)
{
    if (Data.Num() != Width * Height)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid size of color array!"));
        return nullptr;
    }

    UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
    if (!Texture)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create texture!"));
        return nullptr;
    }

    FColor* TextureData = static_cast<FColor*>(Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));
    FMemory::Memcpy(TextureData, Data.GetData(), Data.Num() * sizeof(FColor));

    Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

    Texture->UpdateResource();

    return Texture;
}
*/

void AVideoReader::createAlphaImage(const cv::Mat& Mat, cv::Mat_<cv::Vec4b>& Dst)
{
    std::vector<cv::Mat> matChannels;
    cv::split(Mat, matChannels);

    // create alpha channel
    cv::Mat alpha = matChannels.at(0) + matChannels.at(1) + matChannels.at(2);
    matChannels.push_back(alpha);

    cv::merge(matChannels, Dst);
}


void AVideoReader::ConvertTextureToPixelArray(UTexture2D* Texture2D, TArray<FColor> &PixelArray)
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

bool AVideoReader::ExportImage(UTexture2D* Texture2D, const FString& Path)
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
