// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PreOpenCVHeaders.h"
#include "OpenCVHelper.h"
#include <ThirdParty/OpenCV/include/opencv2/imgproc.hpp>
#include <ThirdParty/OpenCV/include/opencv2/highgui/highgui.hpp>
#include <ThirdParty/OpenCV/include/opencv2/core.hpp>
#include "PostOpenCVHeaders.h"

#include "MocapMpProxy.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	cv::Mat mImage;
	TArray<FColor> mData;

	MocapMpProxy mMocap = MocapMpProxy();

	bool mCanLoadMocapLibrary = false;
	FString mEngineName = "unreal";
	bool mIsCalibrated = false;

	static const int mNumJoints = 68;
	TArray<FVector> mBones;
	TArray<FQuat> mQuats;

	// Facial control parameters
	TArray<float> mFacialCtrlParams;


};
