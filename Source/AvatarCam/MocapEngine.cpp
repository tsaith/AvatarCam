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

	mImage = cv::Mat(ImageHeight, ImageWidth, CV_8UC3, cv::Scalar(0, 0, 0));
	mData.Init(FColor(0, 0, 0, 255), ImageWidth*ImageHeight);

}

// Called every frame
void AMocapEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UPrintBPLibrary::PrintMessage("hi");
	Process();
}


void AMocapEngine::Process() {

	FString msg;
	FString leftStaticGesture;
	FString rightStaticGesture;

	cv::Mat imageDebug;

	// Motion capture 
	if (mCanLoadMocapLibrary) {

	    //UPrintBPLibrary::PrintInt("Width: ", ImageWidth);
	    //UPrintBPLibrary::PrintInt("Height: ", ImageHeight);
		bool bIsEmpty = mImage.empty();
	    //UPrintBPLibrary::PrintBool("is empty: ", bIsEmpty);
		// Image 
		ConvertDataToImage(mData, mImage);

		//std::string imagePath = "C:\\Users\\andrew\\projects\\AvatarCam\\Outputs\\image.jpg";
		//cv::imwrite(imagePath, mImage);

		//cv::imshow("win", mImage);

		//resize(mImage, imageDebug, cv::Size(320, 240));
		//cv::imshow("Original", imageDebug);



		// Detection
		mMocap.Detect(mImage);

		// Perform diagnostics 
		Diagnostic();

	}
}

void AMocapEngine::Diagnostic() {

}


void AMocapEngine::SetImageData(TArray<FColor> Data) {
	mData = Data;
}

void AMocapEngine::Calibrate() {
	mMocap.Calibrate();
}

void AMocapEngine::SetEngineName(FString EngineName) {
	mEngineName = EngineName;
}

FString AMocapEngine::GetEngineName() {
	return mEngineName;
}


void AMocapEngine::GetBones(TArray<FVector>& Bones) {
	Bones = mBones;
}

void AMocapEngine::GetQuats(TArray<FQuat>& Quats) {
	Quats = mQuats;
}


void AMocapEngine::ConvertDataToImage(TArray<FColor>& Data, cv::Mat& Image) {

	uchar* p = Image.data;
	const int numChannels = 3;

	int k = 0;
	int m = 0;
	for (int i = 0; i < ImageHeight; i++) {
		for (int j = 0; j < ImageWidth; j++) {

			k = i * ImageWidth * numChannels + j * numChannels;
			m = i * ImageWidth + j;

			p[k] = Data[m].B;
			p[k + 1] = Data[m].G;
			p[k + 2] = Data[m].R;

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


