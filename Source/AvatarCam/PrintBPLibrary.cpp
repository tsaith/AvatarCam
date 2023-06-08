#include "PrintBPLibrary.h"


void UPrintBPLibrary::PrintMessage(FString Msg, bool ToScreen, bool ToLog) {

	if (ToScreen) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, Msg);
	if (ToLog) UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

}

void UPrintBPLibrary::PrintBool(FString Msg, bool Input, bool ToScreen, bool ToLog) {

	FString s = FString::SanitizeFloat(Input);

	Msg += s;
	PrintMessage(Msg, ToScreen, ToLog);

}

void UPrintBPLibrary::PrintInt(FString Msg, int Input, bool ToScreen, bool ToLog) {

	FString s = FString::SanitizeFloat(Input);

	Msg += s;
	PrintMessage(Msg, ToScreen, ToLog);

}

void UPrintBPLibrary::PrintFloat(FString Msg, float Input, bool ToScreen, bool ToLog) {

	FString s = FString::SanitizeFloat(Input);

	Msg += s;
	PrintMessage(Msg, ToScreen, ToLog);

}

void UPrintBPLibrary::PrintVector(FString Msg, FVector Input, bool ToScreen, bool ToLog) {

	FString s = FString::SanitizeFloat(Input.X) + ", " +
		FString::SanitizeFloat(Input.Y) + ", " + FString::SanitizeFloat(Input.Z);

	Msg += s;
	PrintMessage(Msg, ToScreen, ToLog);

}

void UPrintBPLibrary::PrintRotator(FString Msg, FRotator Input, bool ToScreen, bool ToLog) {

	FString s = FString::SanitizeFloat(Input.Roll) + ", " +
		FString::SanitizeFloat(Input.Pitch) + ", " + FString::SanitizeFloat(Input.Yaw);

	Msg += s;
	PrintMessage(Msg, ToScreen, ToLog);

}

void UPrintBPLibrary::PrintFVector4(FString Msg, FVector4 Input, bool ToScreen, bool ToLog) {

	FString s = FString::SanitizeFloat(Input.W) + ", " + FString::SanitizeFloat(Input.X) + ", " +
		FString::SanitizeFloat(Input.Y) + +", " + FString::SanitizeFloat(Input.Z);

	Msg += s;
	PrintMessage(Msg, ToScreen, ToLog);

}

void UPrintBPLibrary::PrintQuat(FString Msg, FQuat Input, bool ToScreen, bool ToLog) {

	FString s = FString::SanitizeFloat(Input.W) + ", " + FString::SanitizeFloat(Input.X) + ", " +
		FString::SanitizeFloat(Input.Y) + +", " + FString::SanitizeFloat(Input.Z);

	Msg += s;
	PrintMessage(Msg, ToScreen, ToLog);

}

