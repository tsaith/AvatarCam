
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PreOpenCVHeaders.h"
#include "OpenCVHelper.h"
#include <ThirdParty/OpenCV/include/opencv2/imgproc.hpp>
#include <ThirdParty/OpenCV/include/opencv2/highgui/highgui.hpp>
#include <ThirdParty/OpenCV/include/opencv2/core.hpp>
#include "PostOpenCVHeaders.h"

#include "CoreMinimal.h"

/**
 * 
 */
class AVATARCAM_API MocapMpProxy
{
public:
	MocapMpProxy();
	~MocapMpProxy();

    bool LoadLibrary(FString filePath);
    void FreeLibrary();
    void ImportMethods();

    void Init(int width, int height);
    void Finalize();
    void Detect(cv::Mat image);
    void SetEngineName(FString engineName);
    void Calibrate();
    const int GetNumBones();
    const int GetBoneDims();
    const int GetQuatDims();
    float* GetBone(int i);
    float* GetQuat(int i);

    int GetNumFacialCtrlParams();
    void GetFacialCtrlParams(TArray<float> &params);

private:

    // Library handle 
    void* mHandle = NULL;

    // Define method type
    typedef void (*InitT)(int, int);
    typedef void (*FinalizeT)();
    typedef void (*SetEngineNameT)(char*);
    typedef void (*DetectT)(cv::Mat);
    typedef void (*CalibrateT)();

    typedef const int (*GetNumBonesT)();
    typedef const int (*GetBoneDimsT)();
    typedef const int (*GetQuatDimsT)();
    typedef float* (*GetBoneT)(int i);
    typedef float* (*GetQuatT)(int i);

    typedef int (*GetNumFacialCtrlParamsT)();
    typedef float* (*GetFacialCtrlParamsT)();

    InitT mInit = NULL;
    FinalizeT mFinalize = NULL;
    SetEngineNameT mSetEngineName = NULL;
    DetectT mDetect = NULL;
    CalibrateT mCalibrate = NULL;

    GetNumBonesT mGetNumBones = NULL;
    GetBoneDimsT mGetBoneDims = NULL;
    GetQuatDimsT mGetQuatDims = NULL;
    GetBoneT mGetBone = NULL;
    GetQuatT mGetQuat = NULL;

    GetNumFacialCtrlParamsT mGetNumFacialCtrlParams = NULL;
    GetFacialCtrlParamsT mGetFacialCtrlParams = NULL;

};