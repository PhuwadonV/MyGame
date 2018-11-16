#include "BP_WorldContext.h"

#include "Engine/World.h"

bool UBP_WorldContext::ServerTravel(const UObject *WorldContextObject, const FString &URL, bool Absolute, bool ShouldSkipGameNotify) {
	return WorldContextObject->GetWorld()->ServerTravel(URL, Absolute, ShouldSkipGameNotify);
}