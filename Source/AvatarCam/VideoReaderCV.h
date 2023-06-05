
#pragma once

#include "PreOpenCVHeaders.h"
#include "OpenCVHelper.h"
#include <ThirdParty/OpenCV/include/opencv2/imgproc.hpp>
#include <ThirdParty/OpenCV/include/opencv2/highgui/highgui.hpp>
#include <ThirdParty/OpenCV/include/opencv2/core.hpp>
#include "PostOpenCVHeaders.h"

#include "CoreMinimal.h"


class AVATARCAM_API VideoReaderCV
{
public:

    VideoReaderCV();
    ~VideoReaderCV();

    bool Open(int CameraID, int Width, int Height);
    bool Open(FString VideoPath);
    bool Read(cv::Mat& Frame);
    cv::Mat ImageRead(FString ImagePath);
    bool IsOpened();

    void Close();


private:

    cv::VideoCapture mCapture;
    bool mStatus;

    int mWidth = 640;
    int mHeight = 480;

    int mTargetWidth = -1;
    int mTargetHeight = -1;

    int mCameraID = 0;
    int mFPS = 30;

    bool mIsVideo = false;
    int mFrameCounter = 0;
    int mVideoLength = 0;

};
