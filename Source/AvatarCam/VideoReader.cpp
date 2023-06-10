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

    mImageTexture = CreateTextureFromPixelArray(mData, mImage.cols, mImage.rows);

    //mImageTexture = FOpenCVHelper::TextureFromCvMat(mImage);
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
    UTexture2D* Texture;

    Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
    if (!Texture)
    {
        return nullptr;
    }
 
    // Editor only 
    //Texture->MipGenSettings = TMGS_NoMipmaps;

    //Texture->NeverStream = true;

    //Texture->SRGB = 0;

    FTexture2DMipMap& Mip = Texture->PlatformData->Mips[0];
    void* pData = Mip.BulkData.Lock(LOCK_READ_WRITE);

    //FMemory::Memcpy(pData, Data.GetData(), Width * Height * 4);
    FMemory::Memcpy(pData, Data.GetData(), Data.Num() * sizeof(FColor));
    Mip.BulkData.Unlock();
    Texture->UpdateResource();

    return Texture;
}

/*
UTexture2D* CreateTextureFromPixelData(TArray<FColor>& Data, int Width, int Height)
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
