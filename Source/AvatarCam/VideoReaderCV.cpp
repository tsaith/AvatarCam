#include "VideoReaderCV.h"


VideoReaderCV::VideoReaderCV()
{
}

VideoReaderCV::~VideoReaderCV()
{
    Close();
}

bool VideoReaderCV::Open(int CameraID, int Width, int Height)
{

    mIsVideo = false;

    mCameraID = CameraID;
    mWidth = Width;
    mHeight = Height;

    mCapture.open(mCameraID, cv::CAP_DSHOW);
    mStatus = mCapture.isOpened();

    if (mStatus) {

        mCapture.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
        mCapture.set(cv::CAP_PROP_FRAME_WIDTH, mWidth);
        mCapture.set(cv::CAP_PROP_FRAME_HEIGHT, mHeight);
        mCapture.set(cv::CAP_PROP_FPS, mFPS);

    }
    else {
        UE_LOG(LogTemp, Error, TEXT("Error: failed to open the camera."));
    }

    return mStatus;
}

bool VideoReaderCV::Open(FString VideoPath)
{
    mIsVideo = true;

    cv::String path = TCHAR_TO_ANSI(*VideoPath);
    mCapture.open(path);
    mStatus = mCapture.isOpened();

    if (mStatus) {
        mVideoLength = int(mCapture.get(cv::CAP_PROP_FRAME_COUNT));
    }

    return mStatus;
}

bool VideoReaderCV::Read(cv::Mat& Frame)
{
    if (mIsVideo) {

        mFrameCounter += 1;

        // Rewind when video reaches the end. 
        if (mFrameCounter == mVideoLength) {
            mFrameCounter = 0;
            mCapture.set(cv::CAP_PROP_POS_FRAMES, 0);
        }

    }

    if (mCapture.isOpened()) {
        mStatus = mCapture.read(Frame);
    }

    return mStatus;
}

cv::Mat VideoReaderCV::ImageRead(FString ImagePath)
{
    cv::String path = TCHAR_TO_ANSI(*ImagePath);
    cv::Mat image = cv::imread(path);

    return image;
}

bool VideoReaderCV::IsOpened() 
{
    return mCapture.isOpened();
}

void VideoReaderCV::Close()
{
    if (mCapture.isOpened()) mCapture.release();
}

