#pragma once

#include "ExtendBlueprintEngineBase.h"
#include "ExtendBlueprintEngineFunctions.generated.h"

UCLASS()
class UExtendBlueprintEngineFunctions : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Debug", meta = (DevelopmentOnly))
	static void Print(const FString &Message, float TimeToDisplay = 2.0f, FColor DisplayColor = FColor::Cyan);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static TArray<APlayerController*> GetPlayerControllers(const UObject *WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Networking", meta = (WorldContext = "WorldContextObject"))
	static bool ServerTravel(const UObject *WorldContextObject, const FString &URL, bool bAbsolute, bool ShouldSkipGameNotify);

	UFUNCTION(BlueprintCallable, Category = "Networking")
	static void ClientTravel(UPARAM(Ref) APlayerController *PlayerController, const FString &URL, enum ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid);
};