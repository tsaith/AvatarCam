#include "MocapMpProxy.h"

template<typename T>
T GetFuncPointer(void* handle, FString funcName) {

    T fp = (T)FPlatformProcess::GetDllExport(handle, *funcName);
    return fp;

}

MocapMpProxy::MocapMpProxy() {
}

MocapMpProxy::~MocapMpProxy() {
    FreeLibrary();
} 

bool MocapMpProxy::LoadLibrary(FString filePath) {

    mHandle = FPlatformProcess::GetDllHandle(*filePath);

    if (FPaths::FileExists(filePath)) {

        mHandle = FPlatformProcess::GetDllHandle(*filePath);
        if (mHandle != NULL) {
            ImportMethods();
            return true;
        }
    }

    return false;

}

void MocapMpProxy::FreeLibrary() {

    if (mHandle != NULL)
    {
        FPlatformProcess::FreeDllHandle(mHandle);
        mHandle = NULL;
    }

}

void MocapMpProxy::ImportMethods() {

    if (mHandle != NULL)
    {
        mInit = GetFuncPointer<InitT>(mHandle, "MocapMpInit");
        mFinalize = GetFuncPointer<FinalizeT>(mHandle, "MocapMpFinalize");
        mSetEngineName = GetFuncPointer<SetEngineNameT>(mHandle, "MocapMpSetEngineName");
        mDetect = GetFuncPointer<DetectT>(mHandle, "MocapMpDetect");
        mCalibrate = GetFuncPointer<CalibrateT>(mHandle, "MocapMpCalibrate");
        mGetNumBones = GetFuncPointer<GetNumBonesT>(mHandle, "MocapMpGetNumBones");
        mGetBoneDims = GetFuncPointer<GetBoneDimsT>(mHandle, "MocapMpGetBoneDims");
        mGetQuatDims = GetFuncPointer<GetQuatDimsT>(mHandle, "MocapMpGeeQuatDims");
        mGetBone = GetFuncPointer<GetBoneT>(mHandle, "MocapMpGetBone");
        mGetQuat = GetFuncPointer<GetQuatT>(mHandle, "MocapMpGetQuat");

        mGetMpPoseNumBones = GetFuncPointer<GetMpPoseNumBonesT>(mHandle, "MocapMpGetMpPoseNumBones");
        mGetMpPoseBone = GetFuncPointer<GetMpPoseBoneT>(mHandle, "MocapMpGetMpPoseBone");

    }

}

void MocapMpProxy::Init(int width, int height) {

    if (mInit != NULL) {
        mInit(width, height);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mInit is NULL."));
    }

}

void MocapMpProxy::Finalize() {

    if (mFinalize != NULL) {
        mFinalize();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mFinalize is NULL."));
    }

}

void MocapMpProxy::SetEngineName(FString engineName) {

    if (mSetEngineName != NULL) {
        char* name = TCHAR_TO_ANSI(*engineName);
        mSetEngineName(name);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mSetEngineName is NULL."));
    }

}

void MocapMpProxy::Detect(cv::Mat image) {

    if (mDetect != NULL) {
        mDetect(image);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mDetect is NULL."));
    }

}

void MocapMpProxy::Calibrate() {

    if (mCalibrate != NULL) {
        mCalibrate();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mCalibrate is NULL."));
    }

}

const int MocapMpProxy::GetNumBones() {

    if (mGetNumBones != NULL) {
        return mGetNumBones();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mGetNumBones is NULL."));
        return -1;
    }

}

const int MocapMpProxy::GetBoneDims() {

    if (mGetBoneDims != NULL) {
        return mGetBoneDims();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mGetBoneDims is NULL."));
        return -1;
    }

}

const int MocapMpProxy::GetQuatDims() {

    if (mGetQuatDims != NULL) {
        return mGetQuatDims();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mGetQuatDims is NULL."));
        return -1;
    }

}

float* MocapMpProxy::GetBone(int i) {

    float* bone;
    if (mGetBone != NULL) {
        bone = mGetBone(i);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mGetBone is NULL."));
        bone = NULL;
    }

    return bone;
}

float* MocapMpProxy::GetQuat(int i) {

    float* quat;
    if (mGetQuat != NULL) {
         quat = mGetQuat(i);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mGetQuat is NULL."));
        quat = NULL;
    }

    return quat;

}

const int MocapMpProxy::GetMpPoseNumBones() {

    if (mGetMpPoseNumBones != NULL) {
        return mGetMpPoseNumBones();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mGetMpPoseNumBones is NULL."));
        return -1;
    }

}

float* MocapMpProxy::GetMpPoseBone(int i) {

    float* bone;
    if (mGetMpPoseBone != NULL) {
        bone = mGetMpPoseBone(i);
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mGetMpPoseBone is NULL."));
        bone = NULL;
    }

    return bone;
}

TArray<FVector> MocapMpProxy::GetBones() {

    const int num = GetNumBones();
    TArray<FVector> bones;
    
    bones.SetNum(num);
    float* pBone;
    for (int i = 0; i < num; i++) {

        pBone = GetBone(i);

        bones[i].X = pBone[0];
        bones[i].Y = pBone[1];
        bones[i].Z = pBone[2];

    }

    return bones;

}

TArray<FQuat> MocapMpProxy::GetQuats() {

    const int num = GetNumBones();
    TArray<FQuat> quats;
    
    quats.SetNum(num);
    float* pQuat;
    for (int i = 0; i < num; i++) {

        pQuat = GetQuat(i);

        quats[i].W = pQuat[0];
        quats[i].X = pQuat[1];
        quats[i].Y = pQuat[2];
        quats[i].Z = pQuat[3];

    }

    return quats;

}


TArray<FVector> MocapMpProxy::GetMpPoseBones() {

    const int num = GetMpPoseNumBones();
    TArray<FVector> bones;
    
    bones.SetNum(num);
    float* pBone;
    for (int i = 0; i < num; i++) {

        pBone = GetMpPoseBone(i);

        bones[i].X = pBone[0];
        bones[i].Y = pBone[1];
        bones[i].Z = pBone[2];

    }

    return bones;

}

