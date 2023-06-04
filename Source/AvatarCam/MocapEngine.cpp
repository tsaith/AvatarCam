// Fill out your copyright notice in the Description page of Project Settings.


#include "MocapEngine.h"

// Sets default values
AMocapEngine::AMocapEngine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString libPath = FPaths::Combine(FPaths::ProjectDir(), "Libs", "libmocap_mp.dll");
	mMocap.LoadLibrary(libPath);
	UE_LOG(LogTemp, Warning, TEXT("libPath: %s"), *libPath);

	mCanLoadMocapLibrary = mMocap.LoadLibrary(libPath);
	mMocap.Init(ImageWidth, ImageHeight);
	mMocap.SetEngineName(mEngineName);

	if (mCanLoadMocapLibrary) {
		UE_LOG(LogTemp, Warning, TEXT("Mocap: Successful to load library."));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Mocap: Failed to load library."));
	}

	// Bones
	mBones.SetNum(mNumJoints);
	// Quaternions 
	mQuats.SetNum(mNumJoints);

	// Facial control parameters
	//mFacialCtrlParams.SetNum(mMocap.GetNumFacialCtrlParams());


}

AMocapEngine::~AMocapEngine()
{
	mMocap.Finalize();

	if (mCap.isOpened()) {
		mCap.release();
	}
}

// Called when the game starts or when spawned
void AMocapEngine::BeginPlay()
{
	Super::BeginPlay();

	mCap = cv::VideoCapture(0);
	if (!mCap.isOpened()) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to open the webcam."));
	}

	mImage = cv::Mat(ImageHeight, ImageWidth, CV_8UC3, cv::Scalar(0, 0, 0));
}

// Called every frame
void AMocapEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Process();
}


void AMocapEngine::Process() {

	FString msg;
	FString leftStaticGesture;
	FString rightStaticGesture;

	cv::Mat imageDebug;

	// Motion capture 
	if (mCanLoadMocapLibrary) {

		/*
		// Image 
		bool ret = mCap.read(mFrame);
		cv::resize(mFrame, mImage, cv::Size(ImageWidth, ImageHeight));
		imshow("win", mImage);

		// Detection
		mMocap.Detect(mImage);
		*/

		// Perform diagnostics 
		//Diagnostic();

	}
}

void AMocapEngine::ConvertDataToImage(cv::Mat& image, TArray<FColor>& data) {

	uchar* p = image.data;

	int k = 0;
	int m = 0;
	for (int i = 0; i < ImageHeight; i++) {
		for (int j = 0; j < ImageWidth; j++) {
			k = i * ImageWidth * 3 + j * 3;
			m = i * ImageWidth + j;
			p[k] = data[m].B;
			p[k + 1] = data[m].G;
			p[k + 2] = data[m].R;
		}
	}

}

void AMocapEngine::RadianToDegree(float Radian, float& Degree)
{

	Degree = Radian / PI * 180.0;

}

void AMocapEngine::DegreeToRadian(float Degree, float& Radian)
{

	Radian = Degree / 180.0 * PI;

}
void AMocapEngine::MakeAngleAxis(float Angle, FVector Axis, FVector4& AngleAxis)
{

	AngleAxis.W = Angle;
	AngleAxis.X = Axis.X;
	AngleAxis.Y = Axis.Y;
	AngleAxis.Z = Axis.Z;

}

void AMocapEngine::QuatToAngleAxis(FQuat Quat, FVector4& AngleAxis)
{

	float angleRad;
	FVector axis;
	Quat.ToAxisAndAngle(axis, angleRad);

	float angleDeg;
	RadianToDegree(angleRad, angleDeg);
	MakeAngleAxis(angleDeg, axis, AngleAxis);

}

void AMocapEngine::PrintMessage(FString msg) {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
}

void AMocapEngine::PrintFloat(FString msg, float v) {

	FString s = FString::SanitizeFloat(v);

	msg += s;
	PrintMessage(msg);

}

void AMocapEngine::PrintVector(FString msg, FVector v) {

	FString s = FString::SanitizeFloat(v.X) + ", " +
		FString::SanitizeFloat(v.Y) + ", " + FString::SanitizeFloat(v.Z);

	msg += s;
	PrintMessage(msg);

}

void AMocapEngine::PrintQuat(FString msg, FQuat q) {

	FString s = FString::SanitizeFloat(q.W) + ", " + FString::SanitizeFloat(q.X) + ", " +
		FString::SanitizeFloat(q.Y) + +", " + FString::SanitizeFloat(q.Z);

	msg += s;
	PrintMessage(msg);

}


