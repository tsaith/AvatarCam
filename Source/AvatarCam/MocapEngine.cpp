// Fill out your copyright notice in the Description page of Project Settings.


#include "MocapEngine.h"

// Sets default values
AMocapEngine::AMocapEngine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMocapEngine::~AMocapEngine()
{
	//mMocap.Finalize();

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

	// Mocap Live
	mMocapLive.Init(ImageWidth, ImageHeight);

	// Number of bones
	mNumBones = mMocapLive.GetNumBones();

	mSkelTransforms.SetNum(mNumBones);
	mBones.SetNum(mNumBones);
	mQuats.SetNum(mNumBones);


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

	bool bIsEmpty = mImage.empty();
	if (bIsEmpty) return;

	ConvertTextureToCvMat(mImageTexture, mImage);

	// Preprocess 
    cv::cvtColor(mImage, image, cv::COLOR_BGRA2BGR);
    cv::resize(image, image, cv::Size(mWidthTarget, mHeightTarget));

    // Mocap Live
	mMocapLive.Detect(image);

	// Head
    mHeadTransform = mMocapLive.GetHeadTransform();

	msg = FString::Printf(TEXT("mIsFace|Detected: %d"), IsFaceDetected());
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *msg);

	// Update skeleton transforms
	mSkelTransforms = mMocapLive.GetSkelTransforms();

	// Update bones and quats 
	mQuats = mMocapLive.GetQuats();
	mBones = mMocapLive.GetBones();

	// Perform diagnostics 
	Diagnostic();

}

void AMocapEngine::Diagnostic() {

	mImageDiag = mImage.clone();

	//CvPlotLibrary::PlotMpPose2d(mImageDiag, mMpPoseBones);
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
	// to do
}

bool AMocapEngine::IsFaceDetected() {
	return mMocapLive.IsFaceDetected();
}

TArray<float> AMocapEngine::GetBlendshapes() {
	return mMocapLive.GetBlendshapes();
}

FTransform AMocapEngine::GetHeadTransform() {
	return mHeadTransform;
}

TArray<FTransform> AMocapEngine::GetSkelTransforms() {
	return mSkelTransforms;
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



