#include "AvatarController.h"


// Sets default values 
AAvatarController::AAvatarController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the names of blendshapes
	InitBlendshapeNames();

}

// Called when the game starts or when spawned
void AAvatarController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatarController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AAvatarController::IsDataReady() {
	return !mSkelTransforms.IsEmpty();
}

void AAvatarController::SetMocapData(
	TArray<float> Blendshapes,
	FTransform HeadTransform,
	TArray<FTransform> SkelTransforms)
{
	mBlendshapes = Blendshapes;
	mHeadTransform = HeadTransform;
	mSkelTransforms = SkelTransforms;

}

void AAvatarController::GetHeadTransform(FTransform& HeadTransform) {
	HeadTransform = mHeadTransform;
}

void AAvatarController::GetBlendshapeNames(TArray<FString>& BlendshapeNames) {
    BlendshapeNames = mBlendshapeNames;
}

void AAvatarController::GetBlendshapes(TArray<float>& Blendshapes) {
	Blendshapes = mBlendshapes;
}

void AAvatarController::GetSkelTransforms(TArray<FTransform>& SkelTransforms) {
    SkelTransforms = mSkelTransforms;
}

/*
void AAvatarController::GetBones(TArray<FVector>& Bones) {
	Bones = mBones;
}

void AAvatarController::GetQuats(TArray<FQuat>& Quats) {
	Quats = mQuats;
}
*/

int AAvatarController::GetIPelvis() {
	return mIPelvis;
}

int AAvatarController::GetISpine01() {
	return mISpine01;
}

int AAvatarController::GetISpine02() {
	return mISpine02;
}

int AAvatarController::GetISpine03() {
	return mISpine03;
}

int AAvatarController::GetINeck01() {
	return mINeck01;
}

int AAvatarController::GetIHead() {
	return mIHead;
}

int AAvatarController::GetIClavicleL() {
	return mIClavicleL;
}

int AAvatarController::GetIUpperarmL() {
	return mIUpperarmL;
}

int AAvatarController::GetILowerarmL() {
	return mILowerarmL;
}

int AAvatarController::GetILowerarmTwist01L() {
	return mILowerarmTwist01L;
}

int AAvatarController::GetIHandL() {
	return mIHandL;
}

int AAvatarController::GetIClavicleR() {
	return mIClavicleR;
}

int AAvatarController::GetIUpperarmR() {
	return mIUpperarmR;
}

int AAvatarController::GetILowerarmR() {
	return mILowerarmR;
}

int AAvatarController::GetILowerarmTwist01R() {
	return mILowerarmTwist01R;
}

int AAvatarController::GetIHandR() {
	return mIHandR;
}

int AAvatarController::GetIThighL() {
	return mIThighL;
}

int AAvatarController::GetICalfL() {
	return mICalfL;
}

int AAvatarController::GetICalfTwist01L() {
	return mICalfTwist01L;
}

int AAvatarController::GetIFootL() {
	return mIFootL;
}

int AAvatarController::GetIBallL() {
	return mIBallL;
}

int AAvatarController::GetIThighR() {
	return mIThighR;
}

int AAvatarController::GetICalfR() {
	return mICalfR;
}

int AAvatarController::GetICalfTwist01R() {
	return mICalfTwist01R;
}

int AAvatarController::GetIFootR() {
	return mIFootR;
}

int AAvatarController::GetIBallR() {
	return mIBallR;
}

int AAvatarController::GetIThumb01L() {
	return mIThumb01L;
}

int AAvatarController::GetIThumb02L() {
	return mIThumb02L;
}

int AAvatarController::GetIThumb03L() {
	return mIThumb03L;
}

int AAvatarController::GetIThumb04L() {
	return mIThumb04L;
}

int AAvatarController::GetIIndex01L() {
	return mIIndex01L;
}

int AAvatarController::GetIIndex02L() {
	return mIIndex02L;
}

int AAvatarController::GetIIndex03L() {
	return mIIndex03L;
}

int AAvatarController::GetIIndex04L() {
	return mIIndex04L;
}

int AAvatarController::GetIMiddle01L() {
	return mIMiddle01L;
}

int AAvatarController::GetIMiddle02L() {
	return mIMiddle02L;
}

int AAvatarController::GetIMiddle03L() {
	return mIMiddle03L;
}

int AAvatarController::GetIMiddle04L() {
	return mIMiddle04L;
}

int AAvatarController::GetIRing01L() {
	return mIRing01L;
}

int AAvatarController::GetIRing02L() {
	return mIRing02L;
}

int AAvatarController::GetIRing03L() {
	return mIRing03L;
}

int AAvatarController::GetIRing04L() {
	return mIRing04L;
}

int AAvatarController::GetIPinky01L() {
	return mIPinky01L;
}

int AAvatarController::GetIPinky02L() {
	return mIPinky02L;
}

int AAvatarController::GetIPinky03L() {
	return mIPinky03L;
}

int AAvatarController::GetIPinky04L() {
	return mIPinky04L;
}

int AAvatarController::GetIThumb01R() {
	return mIThumb01R;
}

int AAvatarController::GetIThumb02R() {
	return mIThumb02R;
}

int AAvatarController::GetIThumb03R() {
	return mIThumb03R;
}

int AAvatarController::GetIThumb04R() {
	return mIThumb04R;
}

int AAvatarController::GetIIndex01R() {
	return mIIndex01R;
}

int AAvatarController::GetIIndex02R() {
	return mIIndex02R;
}

int AAvatarController::GetIIndex03R() {
	return mIIndex03R;
}

int AAvatarController::GetIIndex04R() {
	return mIIndex04R;
}

int AAvatarController::GetIMiddle01R() {
	return mIMiddle01R;
}

int AAvatarController::GetIMiddle02R() {
	return mIMiddle02R;
}

int AAvatarController::GetIMiddle03R() {
	return mIMiddle03R;
}

int AAvatarController::GetIMiddle04R() {
	return mIMiddle04R;
}

int AAvatarController::GetIRing01R() {
	return mIRing01R;
}

int AAvatarController::GetIRing02R() {
	return mIRing02R;
}

int AAvatarController::GetIRing03R() {
	return mIRing03R;
}

int AAvatarController::GetIRing04R() {
	return mIRing04R;
}

int AAvatarController::GetIPinky01R() {
	return mIPinky01R;
}
 
int AAvatarController::GetIPinky02R() {
	return mIPinky02R;
}

int AAvatarController::GetIPinky03R() {
	return mIPinky03R;
}

int AAvatarController::GetIPinky04R() {
	return mIPinky04R;
}

int AAvatarController::GetISpringL() {
	return mISpringL;
}

int AAvatarController::GetISpringR() {
	return mISpringR;
}

/* Protected methods */

void AAvatarController::InitBlendshapeNames() {

	mBlendshapeNames.Init("", mNumBlendshapes);
	//mBlendshapeNames.SetNum(mNumBlendshapes);

	// Follow the ARKit blendshape names
	mBlendshapeNames[0] = "browInnerUp";
	mBlendshapeNames[1] = "browDownLeft";
	mBlendshapeNames[2] = "browDownRight";
	mBlendshapeNames[3] = "browOuterUpLeft";
	mBlendshapeNames[4] = "browOuterUpRight";
	mBlendshapeNames[5] = "eyeLookUpLeft";
	mBlendshapeNames[6] = "eyeLookUpRight";
	mBlendshapeNames[7] = "eyeLookDownLeft";
	mBlendshapeNames[8] = "eyeLookDownRight";
	mBlendshapeNames[9] = "eyeLookOutLeft";
	mBlendshapeNames[10] = "eyeLookInLeft";
	mBlendshapeNames[11] = "eyeLookInRight";
	mBlendshapeNames[12] = "eyeLookOutRight";
	mBlendshapeNames[13] = "eyeBlinkLeft";
	mBlendshapeNames[14] = "eyeBlinkRight";
	mBlendshapeNames[15] = "eyeSquintLeft";
	mBlendshapeNames[16] = "eyeSquintRight";
	mBlendshapeNames[17] = "eyeWideLeft";
	mBlendshapeNames[18] = "eyeWideRight";
	mBlendshapeNames[19] = "cheekPuff";
	mBlendshapeNames[20] = "cheekSquintLeft";
	mBlendshapeNames[21] = "cheekSquintRight";
	mBlendshapeNames[22] = "noseSneerLeft";
	mBlendshapeNames[23] = "noseSneerRight";
	mBlendshapeNames[24] = "jawOpen";
	mBlendshapeNames[25] = "jawForward";
	mBlendshapeNames[26] = "jawLeft"; 
	mBlendshapeNames[27] = "jawRight";
	mBlendshapeNames[28] = "mouthFunnel";
	mBlendshapeNames[29] = "mouthPucker";
	mBlendshapeNames[30] = "mouthLeft";
	mBlendshapeNames[31] = "mouthRight";
	mBlendshapeNames[32] = "mouthRollUpper";
	mBlendshapeNames[33] = "mouthRollLower";
	mBlendshapeNames[34] = "mouthShrugUpper";
	mBlendshapeNames[35] = "mouthShrugLower";
	mBlendshapeNames[36] = "mouthClose";
	mBlendshapeNames[37] = "mouthSmileLeft";
	mBlendshapeNames[38] = "mouthSmileRight";
	mBlendshapeNames[39] = "mouthFrownLeft";
	mBlendshapeNames[40] = "mouthFrownRight";
	mBlendshapeNames[41] = "mouthDimpleLeft";
	mBlendshapeNames[42] = "mouthDimpleRight";
	mBlendshapeNames[43] = "mouthUpperUpLeft";
	mBlendshapeNames[44] = "mouthUpperUpRight";
	mBlendshapeNames[45] = "mouthLowerDownLeft";
	mBlendshapeNames[46] = "mouthLowerDownRight";
	mBlendshapeNames[47] = "mouthPressLeft";
	mBlendshapeNames[48] = "mouthPressRight";
	mBlendshapeNames[49] = "mouthStretchLeft";
	mBlendshapeNames[50] = "mouthStretchRight";
	mBlendshapeNames[51] = "tougueOut";
}
