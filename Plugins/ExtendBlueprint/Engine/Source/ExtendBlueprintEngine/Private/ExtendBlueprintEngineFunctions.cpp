#include "ExtendBlueprintEngineFunctions.h"
#include "Engine/World.h"

bool UExtendBlueprintEngineFunctions::ServerTravel(const UObject *WorldContextObject, const FString &URL, bool Absolute, bool ShouldSkipGameNotify) {
	return WorldContextObject->GetWorld()->ServerTravel(URL, Absolute, ShouldSkipGameNotify);
}