// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AvatarController.generated.h"


UCLASS()
class AVATARCAM_API AAvatarController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAvatarController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "AvatarController")
		bool IsDataReady();

	UFUNCTION(BlueprintCallable, Category = "AvatarController")
		void SetMocapData(TArray<FVector> Bones, TArray<FQuat> Quats, TArray<float> FacialCtrlParams);

	UFUNCTION(BlueprintPure, Category = "AvatarController")
		void GetMocapData(TArray<FVector>& Bones, TArray<FQuat>& Quats, TArray<float>& FacialCtrlParams);

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        void GetBones(TArray<FVector>& Bones);

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        void GetQuats(TArray<FQuat>& Quats);

    // Bone indexes
	UFUNCTION(BlueprintPure, Category = "AvatarController")
	    int GetIPelvis();

	UFUNCTION(BlueprintPure, Category = "AvatarController")
	    int GetISpine01();

	UFUNCTION(BlueprintPure, Category = "AvatarController")
	    int GetISpine02();

	UFUNCTION(BlueprintPure, Category = "AvatarController")
	    int GetISpine03();

	UFUNCTION(BlueprintPure, Category = "AvatarController")
	    int GetINeck01();

	UFUNCTION(BlueprintPure, Category = "AvatarController")
	    int GetIHead();

	UFUNCTION(BlueprintPure, Category = "AvatarController")
	    int GetIClavicleL();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIUpperarmL();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetILowerarmL();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetILowerarmTwist01L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIHandL();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIClavicleR();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIUpperarmR();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetILowerarmR();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetILowerarmTwist01R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIHandR();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThighL();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetICalfL();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetICalfTwist01L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIFootL();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIBallL();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThighR();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetICalfR();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetICalfTwist01R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIFootR();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIBallR();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThumb01L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThumb02L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThumb03L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThumb04L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIIndex01L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIIndex02L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIIndex03L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIIndex04L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIMiddle01L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIMiddle02L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIMiddle03L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIMiddle04L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIRing01L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIRing02L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIRing03L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIRing04L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIPinky01L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIPinky02L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIPinky03L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIPinky04L();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThumb01R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThumb02R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThumb03R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIThumb04R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIIndex01R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIIndex02R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIIndex03R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIIndex04R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIMiddle01R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIMiddle02R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIMiddle03R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIMiddle04R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIRing01R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIRing02R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIRing03R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIRing04R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIPinky01R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIPinky02R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIPinky03R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetIPinky04R();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetISpringL();

    UFUNCTION(BlueprintPure, Category = "AvatarController")
        int GetISpringR();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
 
	TArray<FVector> mBones;
	TArray<FQuat> mQuats;
	TArray<float> mFacialCtrlParams;

    const int mIPelvis = 0;
    const int mISpine01 = 1;
    const int mISpine02 = 2;
    const int mISpine03 = 3;
    const int mINeck01 = 4;
    const int mIHead = 5;

    const int mIClavicleL = 6;
    const int mIUpperarmL = 7;
    const int mILowerarmL = 8;
    const int mILowerarmTwist01L = 9;
    const int mIHandL = 10;

    const int mIClavicleR = 11;
    const int mIUpperarmR = 12;
    const int mILowerarmR = 13;
    const int mILowerarmTwist01R = 14;
    const int mIHandR = 15;

    const int mIThighL = 16;
    const int mICalfL = 17;
    const int mICalfTwist01L = 18;
    const int mIFootL = 19;
    const int mIBallL = 20;

    const int mIThighR = 21;
    const int mICalfR = 22;
    const int mICalfTwist01R = 23;
    const int mIFootR = 24;
    const int mIBallR = 25;

    const int mIThumb01L = 26;
    const int mIThumb02L = 27;
    const int mIThumb03L = 28;
    const int mIThumb04L = 29;
    const int mIIndex01L = 30;
    const int mIIndex02L = 31;
    const int mIIndex03L = 32;
    const int mIIndex04L = 33;
    const int mIMiddle01L = 34;
    const int mIMiddle02L = 35;
    const int mIMiddle03L = 36;
    const int mIMiddle04L = 37;
    const int mIRing01L = 38;
    const int mIRing02L = 39;
    const int mIRing03L = 40;
    const int mIRing04L = 41;
    const int mIPinky01L = 42;
    const int mIPinky02L = 43;
    const int mIPinky03L = 44;
    const int mIPinky04L = 45;

    const int mIThumb01R = 46;
    const int mIThumb02R = 47;
    const int mIThumb03R = 48;
    const int mIThumb04R = 49;
    const int mIIndex01R = 50;
    const int mIIndex02R = 51;
    const int mIIndex03R = 52;
    const int mIIndex04R = 53;
    const int mIMiddle01R = 54;
    const int mIMiddle02R = 55;
    const int mIMiddle03R = 56;
    const int mIMiddle04R = 57;
    const int mIRing01R = 58;
    const int mIRing02R = 59;
    const int mIRing03R = 60;
    const int mIRing04R = 61;
    const int mIPinky01R = 62;
    const int mIPinky02R = 63;
    const int mIPinky03R = 64;
    const int mIPinky04R = 65;

    const int mISpringL = 66;
    const int mISpringR = 67;

};
