#pragma once

#include "opencv2/opencv.hpp"

#ifdef FACIALEXPRESSIONLIBRARY_EXPORTS
#define FACIALEXPRESSIONLIBRARY_API __declspec(dllexport)
#else
#define FACIALEXPRESSIONLIBRARY_API __declspec(dllimport)
#endif


extern "C" FACIALEXPRESSIONLIBRARY_API void FacialExpressionInit(int FrameWidth, int FrameHeight);
extern "C" FACIALEXPRESSIONLIBRARY_API void FacialExpressionFinalize();
extern "C" FACIALEXPRESSIONLIBRARY_API void FacialExpressionDetect(cv::Mat& Image);
extern "C" FACIALEXPRESSIONLIBRARY_API bool FacialExpressionIsFaceDetected();
extern "C" FACIALEXPRESSIONLIBRARY_API unsigned FacialExpressionGetExprCount();
extern "C" FACIALEXPRESSIONLIBRARY_API float* FacialExpressionGetExpressions();
extern "C" FACIALEXPRESSIONLIBRARY_API const int FacialExpressionGetNumBlendshapes();
extern "C" FACIALEXPRESSIONLIBRARY_API float* FacialExpressionGetBlendshapes();
extern "C" FACIALEXPRESSIONLIBRARY_API float* FacialExpressionGetHeadQuat();
extern "C" FACIALEXPRESSIONLIBRARY_API float* FacialExpressionGetHeadTranslation();

