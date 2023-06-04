#include "VideoReaderActor.h"

// Sets default values
AVideoReaderActor::AVideoReaderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVideoReaderActor::BeginPlay()
{
	Super::BeginPlay();

	mImage = cv::Mat(ImageHeight, ImageWidth, CV_8UC3, cv::Scalar(0, 0, 0));

	// Initialize data array
	Data.Init(FColor(0, 0, 0, 255), ImageWidth * ImageHeight);

	if (AsVideoReader) {

		AsCameraReader = false;
		AsImageReader = false;

		mVideoPath = FPaths::Combine(mVideoDir, VideoFilename);
		mVideoReader.Open(mVideoPath);
	}
	else if(AsCameraReader) {
		AsImageReader = false;

		int cameraID = 0;
		mVideoReader.Open(cameraID, ImageWidth, ImageHeight);

	}
	else {

		FString imagePath = FPaths::Combine(mImageDir, ImageFilename);

		if (FPaths::FileExists(imagePath)) {

			cv::String path = TCHAR_TO_ANSI(*imagePath);
			cv::Mat imageRaw = cv::imread(path);
			cv::resize(imageRaw, mImage, cv::Size(ImageWidth, ImageHeight));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Error: Target image can't be found."));
		}
	}

}

// Called every frame
void AVideoReaderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVideoReaderActor::UpdateImageData()
{

	if (mImage.data)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			for (int x = 0; x < ImageWidth; x++)
			{
				int i = x + (y * ImageWidth);
				Data[i].B = mImage.data[i * 3 + 0];
				Data[i].G = mImage.data[i * 3 + 1];
				Data[i].R = mImage.data[i * 3 + 2];
			}
		}

	}

}

