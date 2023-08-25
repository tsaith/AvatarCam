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


//namespace MocapLive {

class MOCAPLIVE_API MocapLiveCore
{
public:

	MocapLiveCore();
	~MocapLiveCore();

	void Init(int ImageWidth, int ImageHeight);
    void Detect(cv::Mat& Image);
    bool IsFaceDetected();
    TArray<float> GetBlendshapes();
    FTransform GetHeadTransform();
    void ConvertQuatFromNvToUnreal(FQuat& QuatIn, FQuat& QuatOut);


private:

    FTransform MakeTransform(float* pTransform);

    bool mIsFaceDetected = false;
    const int mNumBlendshapes = 52;
    TArray<float> mBlendshapes;
    FTransform mHeadTransform;


};

//} // Namespace
