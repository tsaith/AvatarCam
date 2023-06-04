#pragma once

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

#include <windows.h>

using std::string;

typedef HINSTANCE LibHandleT;
LibHandleT OpenSharedLibrary(string LibPath) {

    std::wstring stemp = std::wstring(LibPath.begin(), LibPath.end());
    LPCWSTR path = stemp.c_str();


    LibHandleT handle = LoadLibrary(path);
    if (handle == 0) {
        std::cout << "Cannot open the library." << std::endl;
    }

    return handle;
}

void CloseSharedLibrary(LibHandleT handle) {
    FreeLibrary(handle);
}

template<typename T>
T GetFuncPointer(LibHandleT handle, string FuncName) {
    T fp = (T)GetProcAddress(handle, FuncName.c_str());
    if (!fp) {
        std::cout << "Cannot load symbol " << FuncName.c_str() << std::endl;
    }

    return fp;
}

class MocapMpProxy {
public:

    MocapMpProxy() {
    }

    ~MocapMpProxy() {
        // Close the library
        CloseSharedLibrary(mHandle);
        mHandle = NULL;
    }

    void LoadLibrary(string LibPath) {
        // Load the shared library
        mHandle = OpenSharedLibrary(LibPath);

        // Define methods
        mInit = GetFuncPointer<InitT>(mHandle, "MocapMpInit");
        mFinalize = GetFuncPointer<FinalizeT>(mHandle, "MocapMpFinalize");
        mSetEngineName = GetFuncPointer<SetEngineNameT>(mHandle, "MocapMpSetEngineName");
        mDetect = GetFuncPointer<DetectT>(mHandle, "MocapMpDetect");
        mCalibrate = GetFuncPointer<CalibrateT>(mHandle, "MocapMpCalibrate");

        mGetNumBones = GetFuncPointer<GetNumBonesT>(mHandle, "MocapMpGetNumBones");
        mGetBoneDims = GetFuncPointer<GetBoneDimsT>(mHandle, "MocapMpGetBoneDims");
        mGetQuatDims = GetFuncPointer<GetQuatDimsT>(mHandle, "MocapMpGetQuatDims");
        mGetBone = GetFuncPointer<GetBoneT>(mHandle, "MocapMpGetBone");
        mGetQuat = GetFuncPointer<GetQuatT>(mHandle, "MocapMpGetQuat");

    }

    int Init(int Width, int Height) {
        return mInit(Width, Height);
    }

    void Finalize(void) {
        mFinalize();
    }

    void SetEngineName(string name) {

        const int len = 80;
        char nameChar[len];
        strcpy_s(nameChar, name.c_str());
        mSetEngineName(nameChar);
    }

    int Detect(cv::Mat image) {
        int Detect_status = mDetect(image);

        return Detect_status;
    }

    void Calibrate(void) {
        mCalibrate();
    };

    const int GetNumBones() {
        return mGetNumBones();
    }

    const int GetBoneDims() {
        return mGetBoneDims();
    }

    const int GetQuatDims() {
        return mGetQuatDims();
    }

    float* GetBone(int i) {
        return mGetBone(i);
    }

    float* GetQuat(int i) {
        return mGetQuat(i);
    }

    std::vector<std::vector<float>> GetBones() {

        const int numBones = GetNumBones();
        int dims = GetBoneDims();

        std::vector<std::vector<float>> bones(numBones, std::vector<float>(dims));
        float* p;

        for (int i = 0; i < numBones; i++) {

            p = GetBone(i);
            for (int j = 0; j < dims; j++) {
                bones[i][j] = p[j];
            }
        }

        return bones;

    }

    std::vector<std::vector<float>> GetQuats() {

        const int numBones = GetNumBones();
        int dims = GetQuatDims();

        std::vector<std::vector<float>> quats(numBones, std::vector<float>(dims));
        float* p;

        for (int i = 0; i < numBones; i++) {

            p = GetQuat(i);
            for (int j = 0; j < dims; j++) {
                quats[i][j] = p[j];
            }
        }

        return quats;

    }

private:

    LibHandleT mHandle; // Hadle for library

    // Define function type
    typedef int (*InitT)(int, int);
    typedef void (*FinalizeT)();
    typedef void (*SetEngineNameT)(string name);
    typedef int (*DetectT)(cv::Mat);
    typedef void (*CalibrateT)();

    typedef const int (*GetNumBonesT)();
    typedef const int (*GetBoneDimsT)();
    typedef const int (*GetQuatDimsT)();
    typedef float* (*GetBoneT)(int i);
    typedef float* (*GetQuatT)(int i);

    InitT mInit;
    FinalizeT mFinalize;
    SetEngineNameT mSetEngineName;
    DetectT mDetect;
    CalibrateT mCalibrate;
    GetNumBonesT mGetNumBones;
    GetBoneDimsT mGetBoneDims;
    GetQuatDimsT mGetQuatDims;
    GetBoneT mGetBone;
    GetQuatT mGetQuat;

};

