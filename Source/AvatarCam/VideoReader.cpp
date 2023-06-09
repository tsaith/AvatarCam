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
    mImageTexture = FOpenCVHelper::TextureFromCvMat(mImage);
}

void AVideoReader::GetData(TArray<FColor>& Data) {
	Data = mData;
}

void AVideoReader::GetImageTexture(UTexture2D* &ImageTexture)
{
	ImageTexture = mImageTexture;
}
