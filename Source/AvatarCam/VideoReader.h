// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VideoReaderCV.h"

#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "ImageUtils.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VideoReader.generated.h"

UCLASS()
class AVATARCAM_API AVideoReader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVideoReader();

    void UpdateImageData();
    void UpdateImageTexture();

    UTexture2D* CreateTextureFromPixelArray(TArray<FColor> &Data, int Width, int Height);
    void ConvertTextureToPixelArray(UTexture2D* Texture2D, TArray<FColor>& PixelArray);

    void createAlphaImage(const cv::Mat& Mat, cv::Mat_<cv::Vec4b>& Dst);

	UFUNCTION(BlueprintCallable, Category = "VideoReader")
        bool ExportImage(UTexture2D* Texture2D, const FString& Path);

	UFUNCTION(BlueprintPure, Category = "VideoReader")
		void GetData(TArray<FColor>& Data);

	UFUNCTION(BlueprintPure, Category = "VideoReader")
		void GetImageTexture(UTexture2D* &ImageTexture);


    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VideoReader")
        int ImageWidth = 640;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VideoReader)
        int ImageHeight = 480;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VideoReader)
        int FPS = 30;

    //Enable reading video
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VideoReader)
        bool AsVideoReader = true;

    //Enable reading video
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VideoReader)
        bool AsCameraReader = false;

    //Enable reading image
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VideoReader)
        bool AsImageReader = false;

    //The video filename
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VideoReader)
        FString VideoFilename = "video.mp4";

    // The device ID opened by the Video Stream
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VideoReader)
        int CameraID = 0;

    //The imgage filename
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = VideoReader)
        FString ImageFilename = "image.jpg";

    // The videos width and height (width, height)
    UPROPERTY(BlueprintReadWrite, Category = VideoReader)
        FVector2D VideoSize;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

    FString ImageDirName = "Images";
    FString VideoDirName = "Videos";
    FString mProjectDir = FPaths::ProjectDir();
    FString mVideoDir = FPaths::Combine(mProjectDir, VideoDirName);
    FString mImageDir = FPaths::Combine(mProjectDir, ImageDirName);

    VideoReaderCV mVideoReader = VideoReaderCV();
    FString mVideoPath;
    FString mImagePath;

    cv::Mat mImage;
    TArray<FColor> mData;
    UTexture2D* mImageTexture = nullptr;

};
