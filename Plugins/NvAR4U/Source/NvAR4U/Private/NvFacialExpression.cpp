
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
    mHeadQuat = FQuat(p[0], p[1], p[2], p[3]);

    p = FacialExpressionGetHeadTranslation();
    mHeadTranslation = FVector(p[0], p[1], p[2]);

}

bool NvFacialExpression::IsFaceDetected()
{
    return mIsFaceDetected;
}

TArray<float> NvFacialExpression::GetBlendshapes()
{
    return mBlendshapes;
}

FQuat NvFacialExpression::GetHeadQuat() 
{
    return mHeadQuat;
}

FVector NvFacialExpression::GetHeadTranslation() 
{
    return mHeadTranslation;
}
