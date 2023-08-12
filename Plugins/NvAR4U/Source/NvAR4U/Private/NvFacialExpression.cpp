
#include "NvFacialExpression.h"
#include "ThirdParty/FacialExpressionLibrary/include/FacialExpressionLibrary.h"

NvFacialExpression::NvFacialExpression()
{
}

NvFacialExpression::~NvFacialExpression()
{
    FacialExpressionFinalize();
}

void NvFacialExpression::Init(int ImageWidth, int ImageHeight)
{
    // Bleadshapes 
    mBlendshapes.SetNum(mNumBlendshapes);
    //mBlendshapes.Init(mNumBlendshapes, 0.0);

    // Initialize Facial Expression
    FacialExpressionInit(ImageWidth, ImageHeight);

}

void NvFacialExpression::Detect(cv::Mat& Image)
{
    float* p;

    FacialExpressionDetect(Image);

    mIsFaceDetected = FacialExpressionIsFaceDetected();
    
    // Blendshapes
    p = FacialExpressionGetBlendshapes();
    for (int i = 0; i < mNumBlendshapes; i++) {
        mBlendshapes[i] = p[i];
    }

    p = FacialExpressionGetHeadQuat();
    FQuat quat = FQuat(p[0], p[1], p[2], p[3]);
    ConvertQuatFromNvToUnreal(quat, mHeadQuat);

    p = FacialExpressionGetHeadTranslation();
    mHeadTranslation = FVector(p[0], p[1], p[2]);

    mHeadTransform = FTransform(mHeadQuat, mHeadTranslation, mHeadScale);

}

bool NvFacialExpression::IsFaceDetected()
{
    return mIsFaceDetected;
}

TArray<float> NvFacialExpression::GetBlendshapes()
{
    return mBlendshapes;
}

FTransform NvFacialExpression::GetHeadTransform() 
{
    return mHeadTransform;
}

FQuat NvFacialExpression::GetHeadQuat() 
{
    return mHeadQuat;
}

FVector NvFacialExpression::GetHeadTranslation() 
{
    return mHeadTranslation;
}

void NvFacialExpression::ConvertQuatFromNvToUnreal(FQuat& QuatIn, FQuat& QuatOut)
{

    float x, y, z, w;
    x = -QuatIn.X;
    y = -QuatIn.Z;
    z = -QuatIn.Y;
    w = QuatIn.W;

    QuatOut = FQuat(x, y, z, w);

}
