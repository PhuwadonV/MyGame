#pragma once

#include "ExtendBlueprintEngineBase.h"
#include "ExtendBlueprintEngineFunctions.generated.h"

UCLASS()
class UExtendBlueprintEngineFunctions : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Networking", meta = (WorldContext = "WorldContextObject"))
	static bool ServerTravel(const UObject *WorldContextObject, const FString &URL, bool Absolute, bool ShouldSkipGameNotify);
};