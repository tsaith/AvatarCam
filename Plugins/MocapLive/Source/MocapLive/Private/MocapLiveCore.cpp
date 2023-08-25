#include "MocapLiveCore.h"

#include "LibMocap.h"

MocapLiveCore::MocapLiveCore()
{
}

MocapLiveCore::~MocapLiveCore()
{
    //MocapFinalize();
}

void MocapLiveCore::Init(int ImageWidth, int ImageHeight)
{
    // Bleadshapes 
    mBlendshapes.SetNum(mNumBlendshapes);
    //mBlendshapes.Init(mNumBlendshapes, 0.0);


    mSkelTransforms.SetNum(mNumBones);
    mQuats.SetNum(mNumBones);
    mBones.SetNum(mNumBones);

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

    // Skeleton
    FTransform transform;
    for (int i = 0; i < mNumBones; i++) { 

        transform = GetSkelTransform(i);
        mSkelTransforms[i] = transform;
        mQuats[i] = transform.GetRotation();
        mBones[i] = transform.GetTranslation();

    }

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

int MocapLiveCore::GetNumBones() 
{
    return mNumBones;
}

FTransform MocapLiveCore::GetSkelTransform(int Index) 
{
    float* p = MocapGetSkelTransform(Index); 
    FTransform transform = MakeTransform(p);

    // Convert quaternion from Mediapipe to Unreal coordinates
    FQuat rotation = transform.GetRotation();
    ConvertQuatFromMpToUnreal(rotation, rotation);
    transform.SetRotation(rotation);

    return transform;
}

TArray<FQuat> MocapLiveCore::GetQuats()
{
    return mQuats;
}

TArray<FVector> MocapLiveCore::GetBones()
{
    return mBones;
}


// Private methods

void MocapLiveCore::ConvertQuatFromNvToUnreal(FQuat& QuatIn, FQuat& QuatOut)
{

    float x, y, z, w;
    x = -QuatIn.X;
    y = -QuatIn.Z;
    z = -QuatIn.Y;
    w = QuatIn.W;

    QuatOut = FQuat(x, y, z, w);

}

void MocapLiveCore::ConvertQuatFromMpToUnreal(FQuat& QuatIn, FQuat& QuatOut)
{

    float x, y, z, w;
    x = -QuatIn.X;
    y = QuatIn.Z;
    z = QuatIn.Y;
    w = QuatIn.W;

    QuatOut = FQuat(x, y, z, w);

}
// Private methods
FTransform MocapLiveCore::MakeTransform(float* pTransform)
{
    FQuat rotation; 
    FVector translation;
    FVector scale3D;

    rotation.X = pTransform[0];
    rotation.Y = pTransform[1];
    rotation.Z = pTransform[2];
    rotation.W = pTransform[3];

    translation.X = pTransform[4];
    translation.Y = pTransform[5];
    translation.Z = pTransform[6];

    scale3D.X = pTransform[7];
    scale3D.Y = pTransform[8];
    scale3D.Z = pTransform[9];

    FTransform transform = FTransform(rotation,
        translation, scale3D);

    return transform;
}

