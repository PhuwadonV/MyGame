#pragma once

#include "ExtendBlueprintEngineBase.h"
#include "ExtendPlayerController.generated.h"

UCLASS()
class UExtendPlayerController : public UObject {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Networking")
	static void ClientTravel(UPARAM() APlayerController *PlayerController, const FString &URL, enum ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid);
};