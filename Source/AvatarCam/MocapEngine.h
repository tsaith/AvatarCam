// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PreOpenCVHeaders.h"
#include "OpenCVHelper.h"
#include <ThirdParty/OpenCV/include/opencv2/opencv.hpp>
//#include <ThirdParty/OpenCV/include/opencv2/imgproc.hpp>
//#include <ThirdParty/OpenCV/include/opencv2/highgui/highgui.hpp>
//#include <ThirdParty/OpenCV/include/opencv2/core.hpp>
#include "PostOpenCVHeaders.h"

#include "MocapMpProxy.h"
#include "PrintBPLibrary.h"

#include "Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MocapEngine.generated.h"

UCLASS()
class AVATARCAM_API AMocapEngine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMocapEngine();
	~AMocapEngine();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Process();
	//void EstimateSkeleton();
	//void UpdateLocomotion();
	void Diagnostic();
	
	void ConvertTextureToCvMat(UTexture2D* &Texture, cv::Mat &M);
	void ConvertCvMatToTexture(cv::Mat &M, UTexture2D* &Texture);

    void AppendAlphaChannel(cv::Mat& Src, cv::Mat& Dst);

	/*
	*/
	cv::Mat CreateMatFromTexture(UTexture2D* Texture);
	void ConvertDataToImage(TArray<FColor>& Data, cv::Mat& Image);
	void RadianToDegree(float Radian, float& Degree);
	void DegreeToRadian(float Degree, float& Radian);
	void MakeAngleAxis(float Angle, FVector Axis, FVector4& AngleAxis);
	void QuatToAngleAxis(FQuat Quat, FVector4& AngleAxis);

	TArray<FVector> ToPixelSpace(TArray<FVector> &Pose, int Width, int Height);
	TArray<FVector> ToNormSpace(TArray<FVector> &Pose, int Width, int Height);


	// Parameters
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = MocapEngine)
		int CameraID = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MocapEngine")
		int ImageWidth = 640;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MocapEngine")
		int ImageHeight = 480;

	// Methods
	UFUNCTION(BlueprintCallable, Category = "MocapEngine")
		void SetImageData(TArray<FColor> Data);

	UFUNCTION(BlueprintCallable, Category = "MocapEngine")
		void SetImageTexture(UTexture2D* ImageTexture);


	UFUNCTION(BlueprintCallable, Category = "MocapEngine")
		void Calibrate();

	UFUNCTION(BlueprintCallable, Category = "MocapEngine")
		void SetEngineName(FString EngineName);

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		FString GetEngineName();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		void GetBones(TArray<FVector>& Bones);

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		void GetQuats(TArray<FQuat>& Quats);

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		void GetData(TArray<FColor>& Data);

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		void GetImageTexture(UTexture2D* &ImageTexture);

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		void GetDiagTexture(UTexture2D* &DiagTexture);

	/*
	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIPelvis();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetISpine01();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetISpine02();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetISpine03();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetINeck01();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIHead();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIClavicleL();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIUpperarmL();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetILowerarmL();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIHandL();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIClavicleR();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIUpperarmR();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetILowerarmR();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIHandR();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIThighL();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetICalfL();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIFootL();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIBallL();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIThighR();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetICalfR();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIFootR();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIBallR();

	// Left fingers
	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIThumb01L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIThumb02L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIThumb03L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIIndex01L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIIndex02L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIIndex03L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIMiddle01L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIMiddle02L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIMiddle03L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIRing01L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIRing02L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIRing03L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIPinky01L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIPinky02L();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIPinky03L();

	// Right fingers
	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIThumb01R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIThumb02R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIThumb03R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIIndex01R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIIndex02R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIIndex03R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIMiddle01R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIMiddle02R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIMiddle03R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIRing01R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIRing02R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIRing03R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIPinky01R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIPinky02R();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		int GetIPinky03R();

	// Facial expression
	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		TArray<float> GetFacialCtrlParams();

	// Gestures
	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		FString GetLeftStaticGesture();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		FString GetRightStaticGesture();

	// Locomotion
	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		bool IsSquat();
	*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
 
	cv::VideoCapture mCap;
	cv::Mat mFrame;
	cv::Mat mImage;
	cv::Mat mImageDiag;
	TArray<FColor> mData;
	UTexture2D* mImageTexture = nullptr;
	UTexture2D* mDiagTexture = nullptr;

	const int mWidthTarget = 640;
	const int mHeightTarget = 480;

	MocapMpProxy mMocap = MocapMpProxy();

	bool mCanLoadMocapLibrary = false;
	FString mEngineName = "unreal";
	bool mIsCalibrated = false;

	int mNumBones = -1;
	TArray<FVector> mBones;
	TArray<FQuat> mQuats;

	TArray<FVector> mMpPoseBones;

	// Facial control parameters
	TArray<float> mFacialCtrlParams;


};
