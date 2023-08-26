#pragma once

#include "opencv2/opencv.hpp"

#ifdef LIBFACIALEXPRESSION_EXPORTS
#define LIBFACIALEXPRESSION_API __declspec(dllexport)
#else
#define LIBFACIALEXPRESSION_API __declspec(dllimport)
#endif


extern "C" LIBFACIALEXPRESSION_API void FacialExpressionInit(int FrameWidth, int FrameHeight);
extern "C" LIBFACIALEXPRESSION_API void FacialExpressionFinalize();
extern "C" LIBFACIALEXPRESSION_API void FacialExpressionDetect(cv::Mat& Image);
extern "C" LIBFACIALEXPRESSION_API bool FacialExpressionIsFaceDetected();
extern "C" LIBFACIALEXPRESSION_API unsigned FacialExpressionGetExprCount();
extern "C" LIBFACIALEXPRESSION_API float* FacialExpressionGetExpressions();
extern "C" LIBFACIALEXPRESSION_API const int FacialExpressionGetNumBlendshapes();
extern "C" LIBFACIALEXPRESSION_API float* FacialExpressionGetBlendshapes();
extern "C" LIBFACIALEXPRESSION_API float* FacialExpressionGetHeadQuat();
extern "C" LIBFACIALEXPRESSION_API float* FacialExpressionGetHeadTranslation();

