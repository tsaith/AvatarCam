// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PreOpenCVHeaders.h"  
#include "OpenCVHelper.h"
#include <ThirdParty/OpenCV/include/opencv2/opencv.hpp>
#include "PostOpenCVHeaders.h"

#include "MocapData.h"
#include "MocapMpProxy.h"
#include "NvFacialExpression.h"

#include "Math/UnrealMathUtility.h"

#include "PrintBPLibrary.h"

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

	//UFUNCTION(BlueprintPure, Category = "MocapEngine")
	    MocapData GetMocapData();

	UFUNCTION(BlueprintCallable, Category = "MocapEngine")
		void Calibrate();

	UFUNCTION(BlueprintCallable, Category = "MocapEngine")
		void SetEngineName(FString EngineName);

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		FString GetEngineName();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		bool IsFaceDetected();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		TArray<float> GetBlendshapes();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		FQuat GetHeadQuat();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		FVector GetHeadTranslation();

	UFUNCTION(BlueprintPure, Category = "MocapEngine")
		void GetMocapData(TArray<float>& Blendshapes,
			TArray<FVector>& Bones, TArray<FQuat>& Quats);

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

	// Facial expression
	NvFacialExpression mFacialExpression = NvFacialExpression();

	// Mocap of Mediapipe
	MocapMpProxy mMocap = MocapMpProxy();

	bool mCanLoadMocapLibrary = false;
	FString mEngineName = "unreal";
	bool mIsCalibrated = false;

	int mNumBones = -1;
	TArray<FVector> mBones;
	TArray<FQuat> mQuats;

	TArray<FVector> mMpPoseBones;


};
