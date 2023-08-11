#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PrintBPLibrary.generated.h"

/*
	Print Blueprint Library
 */

UCLASS()
class AVATARCAM_API UPrintBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "PrintBPLibrary")
	static void PrintMessage(FString Msg, bool ToScreen=true, bool ToLog=true);

	/*
	UFUNCTION(BlueprintCallable, Category = "PrintBPLibrary")
	static void PrintString(FString Msg, FString S, bool ToScreen = true, bool ToLog = true);
	*/

	UFUNCTION(BlueprintCallable, Category = "PrintBPLibrary")
	static void PrintBool(FString Msg, bool Input, bool ToScreen = true, bool ToLog = true);

	UFUNCTION(BlueprintCallable, Category = "PrintBPLibrary")
	static void PrintInt(FString Msg, int Input, bool ToScreen = true, bool ToLog = true);

	UFUNCTION(BlueprintCallable, Category = "PrintBPLibrary")
	static void PrintFloat(FString Msg, float Input, bool ToScreen = true, bool ToLog = true);

	UFUNCTION(BlueprintCallable, Category = "PrintBPLibrary")
	static void PrintVector(FString Msg, FVector Input, bool ToScreen = true, bool ToLog = true);

	UFUNCTION(BlueprintCallable, Category = "PrintBPLibrary")
	static void PrintRotator(FString Msg, FRotator Input, bool ToScreen = true, bool ToLog = true);

	UFUNCTION(BlueprintCallable, Category = "PrintBPLibrary")
	static void PrintFVector4(FString Msg, FVector4 Input, bool ToScreen = true, bool ToLog = true);

	UFUNCTION(BlueprintCallable, Category = "PrintBPLibrary")
	static void PrintQuat(FString Msg, FQuat Input, bool ToScreen = true, bool ToLog = true);

};
