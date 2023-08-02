// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PreOpenCVHeaders.h"  
#include "OpenCVHelper.h"
#include <ThirdParty/OpenCV/include/opencv2/opencv.hpp>
#include "PostOpenCVHeaders.h"

#include <string>
#include <vector>
#include <iostream>

#include "CoreMinimal.h"

using namespace std;

class NVAR4U_API NvFacialExpression {

public:

	NvFacialExpression();
	~NvFacialExpression();
	void Init(int ImageWidth, int ImageHeight);
    void Detect(cv::Mat& Image);
    bool IsFaceDetected();
    TArray<float> GetBlendshapes();
    FQuat GetHeadQuat();
    FVector GetHeadTranslation();


private:

    bool mIsFaceDetected = false;
    const int mNumBlendshapes = 52;
    TArray<float> mBlendshapes;
    FQuat mHeadQuat = FQuat(0.0, 0.0, 0.0, 1.0);
    FVector mHeadTranslation = FVector(0.0, 0.0, 0.0);

};
