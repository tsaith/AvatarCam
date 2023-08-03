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

	// Number of bones
	mNumBones = mMocap.GetNumBones();
	//UPrintBPLibrary::PrintInt("NumBones: ", mMocap.GetNumBones());

	// Bones
	mBones.SetNum(mNumBones);

	// Quaternions 
	mQuats.SetNum(mNumBones);

	// Facial control parameters
	//mFacialCtrlParams.SetNum(mMocap.GetNumFacialCtrlParams());

	// Facial expression
	mFacialExpression.Init(ImageWidth, ImageHeight);


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

	mImage = cv::Mat(ImageHeight, ImageWidth, CV_8UC4, cv::Scalar(0, 0, 0, 255));
	mData.Init(FColor(0, 0, 0, 255), ImageWidth*ImageHeight);

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

	cv::Mat image;
	cv::Mat imageDebug;

	bool bIsFaceDetected = false;
	TArray<float> blendshapes;

	// Motion capture 
	if (mCanLoadMocapLibrary) {

		bool bIsEmpty = mImage.empty();
		if (bIsEmpty) return;

		ConvertTextureToCvMat(mImageTexture, mImage);
		//ConvertDataToImage(mData, mImage);

		// Preprocess 
	    cv::cvtColor(mImage, image, cv::COLOR_BGRA2BGR);
        cv::resize(image, image, cv::Size(mWidthTarget, mHeightTarget));

		// Motion capture
		mMocap.Detect(image);

		// Facial expression
		mFacialExpression.Detect(image);

		msg = FString::Printf(TEXT("mIsFace|Detected: %d"), IsFaceDetected());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *msg);

		msg = FString::Printf(TEXT("jawOpen: %f"), GetBlendshapes()[24]);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *msg);

		// Update bones and quats 
		mBones = mMocap.GetBones();
		mQuats = mMocap.GetQuats();

		mMpPoseBones = mMocap.GetMpPoseBones();
		mMpPoseBones = ToPixelSpace(mMpPoseBones, mWidthTarget, mHeightTarget);

		//int iRightWrist = 15;
		//FVector rightWrist = mBones[iRightWrist];
	    //UPrintBPLibrary::PrintVector("RightWrist: ", rightWrist);

		// Perform diagnostics 
		Diagnostic();

	}
}

void AMocapEngine::Diagnostic() {

	mImageDiag = mImage.clone();

	CvPlotLibrary::PlotMpPose2d(mImageDiag, mMpPoseBones);
	ConvertCvMatToTexture(mImageDiag, mDiagTexture);

}

void AMocapEngine::ConvertTextureToCvMat(UTexture2D* &Texture, cv::Mat &Mat) {

	if (Texture == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Texture is nullptr."));
		return;
	}

	// Ensure the format
	if (Texture->GetPixelFormat() != PF_B8G8R8A8) {
		UE_LOG(LogTemp, Error, TEXT("Texture pixel format is not BGRA8."));
		return;
	}

	// Lock and get data
	FTexture2DMipMap& Mip = Texture->GetPlatformData()->Mips[0];
	void* Data = Mip.BulkData.Lock(LOCK_READ_ONLY);
	int32 Width = Mip.SizeX, Height = Mip.SizeY;

	// Create a Mat
	Mat = cv::Mat(Height, Width, CV_8UC4, Data);

	// Unlock data
	Mip.BulkData.Unlock();

}

void AMocapEngine::ConvertCvMatToTexture(cv::Mat &Mat, UTexture2D* &Texture) {

	Texture = FOpenCVHelper::TextureFromCvMat(Mat);

}

void AMocapEngine::AppendAlphaChannel(cv::Mat &Src, cv::Mat &Dst) {

    assert(Src.channels() == 3);

    std::vector<cv::Mat> channels;

    cv::split(Src, channels);

    cv::Mat alpha(Src.rows, Src.cols, CV_8UC1, cv::Scalar(255));
    channels.push_back(alpha);

    cv::merge(channels, Dst);

}

void AMocapEngine::SetImageData(TArray<FColor> Data) {
	mData = Data;
}

void AMocapEngine::SetImageTexture(UTexture2D* ImageTexture) {
	mImageTexture = ImageTexture;
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

bool AMocapEngine::IsFaceDetected() {
	return mFacialExpression.IsFaceDetected();
}

TArray<float> AMocapEngine::GetBlendshapes() {
	return mFacialExpression.GetBlendshapes();
}

FQuat AMocapEngine::GetHeadQuat() {
	return mFacialExpression.GetHeadQuat();
}

FVector AMocapEngine::GetHeadTranslation() {
	return mFacialExpression.GetHeadTranslation();
}

void AMocapEngine::GetMocapData(TArray<float>& Blendshapes,
	TArray<FVector>& Bones, TArray<FQuat>& Quats) {

	Blendshapes = GetBlendshapes();
	Bones = mBones;
	Quats = mQuats;

}


void AMocapEngine::GetBones(TArray<FVector> &Bones) {
	Bones = mBones;
}

void AMocapEngine::GetQuats(TArray<FQuat> &Quats) {
	Quats = mQuats;
}

void AMocapEngine::GetData(TArray<FColor> &Data) {
	Data = mData;
}

void AMocapEngine::GetImageTexture(UTexture2D* &ImageTexture)
{
	ImageTexture = mImageTexture;
}

void AMocapEngine::GetDiagTexture(UTexture2D* &DiagTexture)
{
	DiagTexture = mDiagTexture;
}

void AMocapEngine::ConvertDataToImage(TArray<FColor> &Data, cv::Mat &Image) {

	uchar* p = Image.data;
	const int numChannels = 4;

	int k = 0;
	int m = 0;
	for (int i = 0; i < ImageHeight; i++) {
		for (int j = 0; j < ImageWidth; j++) {

			k = i * ImageWidth * numChannels + j * numChannels;
			m = i * ImageWidth + j;

			p[k] = Data[m].B;
			p[k + 1] = Data[m].G;
			p[k + 2] = Data[m].R;
			p[k + 3] = Data[m].A;

		}
	}

}

void AMocapEngine::RadianToDegree(float Radian, float &Degree)
{

	Degree = Radian / PI * 180.0;

}

void AMocapEngine::DegreeToRadian(float Degree, float &Radian)
{

	Radian = Degree / 180.0 * PI;

}
void AMocapEngine::MakeAngleAxis(float Angle, FVector Axis, FVector4 &AngleAxis)
{

	AngleAxis.W = Angle;
	AngleAxis.X = Axis.X;
	AngleAxis.Y = Axis.Y;
	AngleAxis.Z = Axis.Z;

}

void AMocapEngine::QuatToAngleAxis(FQuat Quat, FVector4 &AngleAxis)
{

	float angleRad;
	FVector axis;
	Quat.ToAxisAndAngle(axis, angleRad);

	float angleDeg;
	RadianToDegree(angleRad, angleDeg);
	MakeAngleAxis(angleDeg, axis, AngleAxis);

}

cv::Mat AMocapEngine::CreateMatFromTexture(UTexture2D* Texture) {

	if (Texture == nullptr) {
		return cv::Mat();
	}

	// Ensure the format
	if (Texture->GetPixelFormat() != PF_B8G8R8A8) {
		UE_LOG(LogTemp, Error, TEXT("Texture pixel format is not BGRA8."));
		return cv::Mat();
	}

	// Lock and get data
	FTexture2DMipMap& Mip = Texture->GetPlatformData()->Mips[0];
	void* Data = Mip.BulkData.Lock(LOCK_READ_ONLY);
	int32 Width = Mip.SizeX, Height = Mip.SizeY;

	// Create a Mat
	cv::Mat Mat(Height, Width, CV_8UC4, Data);

	// Unlock data
	Mip.BulkData.Unlock();

	// Convert BGRA to BGR
	cv::cvtColor(Mat, Mat, cv::COLOR_BGRA2BGR);

	return Mat;
}

TArray<FVector> AMocapEngine::ToPixelSpace(TArray<FVector> &Pose, int Width, int Height) {

	TArray<FVector> poseOut;
	int num = Pose.Num();

	poseOut.SetNum(num);
	for (int i = 0; i < num; i++) {
		poseOut[i][0] = Pose[i][0] * Width;
		poseOut[i][1] = Pose[i][1] * Height;
	}

	return poseOut;

}

TArray<FVector> AMocapEngine::ToNormSpace(TArray<FVector> &Pose, int Width, int Height) {

	TArray<FVector> poseOut;
	int num = Pose.Num();

	for (int i = 0; i < num; i++) {
		poseOut[i][0] = Pose[i][0] / Width;
		poseOut[i][1] = Pose[i][1] / Height;
	}

	return poseOut;

}



