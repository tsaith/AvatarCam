#include "MocapLiveCore.h"

#include "LibMocap.h"

MocapLiveCore::MocapLiveCore()
{
}

MocapLiveCore::~MocapLiveCore()
{
    MocapFinalize();
}

void MocapLiveCore::Init(int ImageWidth, int ImageHeight)
{
    // Bleadshapes 
    mBlendshapes.SetNum(mNumBlendshapes);
    //mBlendshapes.Init(mNumBlendshapes, 0.0);

    // Initialize Facial Expression
    MocapInit(ImageWidth, ImageHeight);

}

void MocapLiveCore::Detect(cv::Mat& Image)
{
    float* p;

    MocapDetect(Image);

    mIsFaceDetected = MocapIsFaceDetected();
    
    // Blendshapes
    p = MocapGetBlendshapes();
    for (int i = 0; i < mNumBlendshapes; i++) {
        mBlendshapes[i] = p[i];
    }

    // Head transform
    p = MocapGetHeadTransform();
    mHeadTransform = MakeTransform(p);

    FQuat rotation = mHeadTransform.GetRotation();
    ConvertQuatFromNvToUnreal(rotation, rotation);
    mHeadTransform.SetRotation(rotation);

}

bool MocapLiveCore::IsFaceDetected()
{
    return mIsFaceDetected;
}

TArray<float> MocapLiveCore::GetBlendshapes()
{
    return mBlendshapes;
}

FTransform MocapLiveCore::GetHeadTransform() 
{
    return mHeadTransform;
}

void MocapLiveCore::ConvertQuatFromNvToUnreal(FQuat& QuatIn, FQuat& QuatOut)
{

    float x, y, z, w;
    x = -QuatIn.X;
    y = -QuatIn.Z;
    z = -QuatIn.Y;
    w = QuatIn.W;

    QuatOut = FQuat(x, y, z, w);

}



// Private methods
FTransform MocapLiveCore::MakeTransform(float* pTransform)
{
    FVector translation;
    FQuat rotation;
    FVector scale3D;

    translation.X = pTransform[0];
    translation.Y = pTransform[1];
    translation.Z = pTransform[2];

    rotation.X = pTransform[3];
    rotation.Y = pTransform[4];
    rotation.Z = pTransform[5];
    rotation.W = pTransform[6];

    scale3D.X = pTransform[7];
    scale3D.Y = pTransform[8];
    scale3D.Z = pTransform[9];

    FTransform transform = FTransform(rotation,
        translation, scale3D);

    return transform;
}

