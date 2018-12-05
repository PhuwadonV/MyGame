#include "ExtendBlueprintEngineFunctions.h"

#if !UE_BUILD_SHIPPING
#include "Engine.h"
#endif

void UExtendBlueprintEngineFunctions::Print(const FString &Message, float TimeToDisplay, FColor DisplayColor) {
	GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, DisplayColor, Message);
}

TArray<APlayerController*> UExtendBlueprintEngineFunctions::GetPlayerControllers(const UObject *WorldContextObject) {
	TArray<APlayerController*> Players;
	for (auto Player = WorldContextObject->GetWorld()->GetPlayerControllerIterator(); Player; ++Player)
	{
		Players.Add(Player->Get());
	}
	return Players;
}

bool UExtendBlueprintEngineFunctions::ServerTravel(const UObject *WorldContextObject, const FString &URL, bool bAbsolute, bool ShouldSkipGameNotify) {
	return WorldContextObject->GetWorld()->ServerTravel(URL, bAbsolute, ShouldSkipGameNotify);
}

void UExtendBlueprintEngineFunctions::ClientTravel(APlayerController *PlayerController, const FString &URL, enum ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid) {
	PlayerController->ClientTravel(URL, TravelType, bSeamless, MapPackageGuid);
}