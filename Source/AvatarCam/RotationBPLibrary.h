#pragma once

#include "Math/UnrealMathUtility.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RotationBPLibrary.generated.h"

/*
     Rotation Blueprint Library
 */

UCLASS()
class URotationBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void RadianToDegree(float Radian, float& degree);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void DegreeToRadian(float Degree, float& Radian);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void MakeAngleAxis(float Angle, FVector Axis, FVector4& AngleAxis);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void BreakAngleAxis(FVector4 AngleAxis, float& Angle, FVector& Axis);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void MakeQuatFromAngleAxis(FVector4 AngleAxis, FQuat& Quat);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void QuatToRotator(FQuat Quat, FRotator& Rotator);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void RotatorToQuat(FRotator Rotator, FQuat& Quat);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void QuatToAngleAxis(FQuat Quat, FVector4& AngleAxis);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void AngleAxisToQuat(FVector4 AngleAxis, FQuat& Quat);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void RotatorToAngleAxis(FRotator Rotator, FVector4& AngleAxis);

    UFUNCTION(BlueprintPure, Category = "RotationBPLibrary")
    static void AngleAxisToRotator(FVector4 AngleAxis, FRotator& Rotator);

};
