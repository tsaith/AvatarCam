#include "RotationBPLibrary.h"


void URotationBPLibrary::RadianToDegree(float Radian, float& Degree)
{

	Degree = Radian / PI * 180.0;

}

void URotationBPLibrary::DegreeToRadian(float Degree, float& Radian)
{

	Radian = Degree / 180.0 * PI;

}

void URotationBPLibrary::MakeAngleAxis(float Angle, FVector Axis, FVector4& AngleAxis)
{

	AngleAxis.W = Angle;
	AngleAxis.X = Axis.X;
	AngleAxis.Y = Axis.Y;
	AngleAxis.Z = Axis.Z;

}

void URotationBPLibrary::BreakAngleAxis(FVector4 AngleAxis, float& Angle, FVector& Axis)
{

	Angle = AngleAxis.W;
	Axis.X = AngleAxis.X;
	Axis.Y = AngleAxis.Y;
	Axis.Z = AngleAxis.Z;

}

void URotationBPLibrary::MakeQuatFromAngleAxis(FVector4 AngleAxis, FQuat& Quat)
{

	FVector axis(AngleAxis.X, AngleAxis.Y, AngleAxis.Z);
	float angle = AngleAxis.W;

	FQuat quat(axis, angle);
	Quat = quat;

}

void URotationBPLibrary::QuatToRotator(FQuat Quat, FRotator& Rotator)
{
	Rotator = Quat.Rotator();
}

void URotationBPLibrary::RotatorToQuat(FRotator Rotator, FQuat& Quat)
{
	Quat = Rotator.Quaternion();
}

void URotationBPLibrary::QuatToAngleAxis(FQuat Quat, FVector4& AngleAxis)
{

	float angleRad;
	FVector axis;
	Quat.ToAxisAndAngle(axis, angleRad);

	float angleDeg;
	RadianToDegree(angleRad, angleDeg);
	MakeAngleAxis(angleDeg, axis, AngleAxis);

}

void URotationBPLibrary::AngleAxisToQuat(FVector4 AngleAxis, FQuat& Quat)
{

	float angle;
	float angleRad;

	FVector axis;
	BreakAngleAxis(AngleAxis, angle, axis);
	DegreeToRadian(angle, angleRad);
	FQuat quat(axis, angleRad);
	//FQuat quat(axis, angle/PI);
	Quat = quat;

}

void URotationBPLibrary::RotatorToAngleAxis(FRotator Rotator, FVector4& AngleAxis)
{
	FQuat quat;
	RotatorToQuat(Rotator, quat);
	QuatToAngleAxis(quat, AngleAxis);

}

void URotationBPLibrary::AngleAxisToRotator(FVector4 AngleAxis, FRotator& Rotator)
{
	FQuat quat;
	AngleAxisToQuat(AngleAxis, quat);
	QuatToRotator(quat, Rotator);

}
