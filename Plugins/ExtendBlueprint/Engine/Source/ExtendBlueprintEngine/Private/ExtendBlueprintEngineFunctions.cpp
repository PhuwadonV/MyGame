#include "ExtendBlueprintEngineFunctions.h"
#include "Engine/World.h"

bool UExtendBlueprintEngineFunctions::ServerTravel(const UObject *WorldContextObject, const FString &URL, bool bAbsolute, bool ShouldSkipGameNotify) {
	return WorldContextObject->GetWorld()->ServerTravel(URL, bAbsolute, ShouldSkipGameNotify);
}

void UExtendBlueprintEngineFunctions::SeamlessTravel(const UObject *WorldContextObject, const FString &URL, bool bAbsolute, FGuid MapPackageGuid) {
	return WorldContextObject->GetWorld()->SeamlessTravel(URL, bAbsolute, MapPackageGuid);
}