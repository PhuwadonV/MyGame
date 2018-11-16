#include "BP_PlayerController.h"

void UBP_PlayerController::ClientTravel(APlayerController *PlayerController, const FString &URL, enum ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid) {
	PlayerController->ClientTravel(URL, TravelType, bSeamless, MapPackageGuid);
}