#include "ExtendBlueprintEngineFunctions.h"
#include "Engine/World.h"

bool UExtendBlueprintEngineFunctions::ServerTravel(const UObject *WorldContextObject, const FString &URL, bool bAbsolute, bool ShouldSkipGameNotify) {
	return WorldContextObject->GetWorld()->ServerTravel(URL, bAbsolute, ShouldSkipGameNotify);
}

void UExtendBlueprintEngineFunctions::ClientTravel(APlayerController *PlayerController, const FString &URL, enum ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid) {
	PlayerController->ClientTravel(URL, TravelType, bSeamless, MapPackageGuid);
}