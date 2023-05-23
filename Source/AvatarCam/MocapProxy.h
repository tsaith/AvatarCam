// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <string>
#include <iostream>

#include "CoreMinimal.h"

#include <OpenCVHelper.h>
//#include "opencv2/calib3d.hpp"
#include "opencv2/core.hpp"
//#include "opencv2/opencv.hpp"

class AVATARCAM_API MocapProxy
{
public:
	MocapProxy();
	~MocapProxy();

	cv::Mat m;
};
