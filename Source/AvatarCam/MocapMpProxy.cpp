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
        //mGetNumFacialCtrlParams = GetFuncPointer<GetNumFacialCtrlParamsT>(mHandle, "MocapMpGetNumFacialCtrlParams");
        //mGetFacialCtrlParams = GetFuncPointer<GetFacialCtrlParamsT>(mHandle, "MocapMpGetFacialCtrlParams");
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

/*
int MocapMpProxy::GetNumFacialCtrlParams() {

    int num;
    if (mGetNumFacialCtrlParams != NULL) {
        num = mGetNumFacialCtrlParams();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mGetNumFacialCtrlParams is NULL."));
    }
    return num;

}

void MocapMpProxy::GetFacialCtrlParams(TArray<float> &params) {

    float* ptr = NULL;
    int i;

    if (mGetFacialCtrlParams != NULL) {

        ptr = mGetFacialCtrlParams();
        for (i = 0; i < params.Num(); i++) {
            params[i] = ptr[i];
        }

    } else {
        UE_LOG(LogTemp, Warning, TEXT("Error: mGetFacialCtrlParams is NULL."));
    }

}
*/
