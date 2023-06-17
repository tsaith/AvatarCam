// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PreOpenCVHeaders.h"
#include "OpenCVHelper.h"
#include <ThirdParty/OpenCV/include/opencv2/imgproc.hpp>
#include <ThirdParty/OpenCV/include/opencv2/highgui/highgui.hpp>
#include <ThirdParty/OpenCV/include/opencv2/core.hpp>
#include "PostOpenCVHeaders.h"


#include "CoreMinimal.h"

class AVATARCAM_API CvPlotLibrary
{
public:

	static TArray<TArray<int>> GetPoseConnect();
	static TArray<TArray<int>> GetMpPoseConnect();

	static void PlotPose2d(cv::Mat& Image, TArray<FVector> &Pose);
	static void PlotMpPose2d(cv::Mat& Image, TArray<FVector> &Pose);
};
