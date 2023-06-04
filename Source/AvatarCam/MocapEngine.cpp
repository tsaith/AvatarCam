// Fill out your copyright notice in the Description page of Project Settings.


#include "MocapEngine.h"

// Sets default values
AMocapEngine::AMocapEngine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString filePath = FPaths::Combine(FPaths::GetProjectFilePath(), "Libs", "libmocap_mp.dll");
	mMocap.LoadLibrary(filePath);
}

// Called when the game starts or when spawned
void AMocapEngine::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AMocapEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	cv::Mat test(cv::Size(1, 49), CV_32FC3);
	//ExampleLibraryFunction();
}

