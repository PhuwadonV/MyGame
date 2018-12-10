#pragma once

#include "ExtendBlueprintEngineBase.h"
#include "ExtendBlueprintEngineFunctions.generated.h"

UCLASS()
class UExtendBlueprintEngineFunctions : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static TArray<APlayerController*> GetPlayerControllers(const UObject *WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Networking", meta = (WorldContext = "WorldContextObject"))
	static bool ServerTravel(const UObject *WorldContextObject, const FString &URL, bool bAbsolute, bool ShouldSkipGameNotify);

	UFUNCTION(BlueprintCallable, Category = "Networking")
	static void ClientTravel(UPARAM() APlayerController *PlayerController, const FString &URL, enum ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid);

	UFUNCTION(BlueprintPure)
	static FUniqueNetIdRepl UniqueID(UPARAM() APlayerState *PlayerState);

	UFUNCTION(BlueprintPure)
	static FString ToString(UPARAM(Ref) const FUniqueNetIdRepl &UniqueNetIdRepl);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal UniqueNetId", CompactNodeTitle = "==", Keywords = "== equal"))
	static bool CompareEqualily(UPARAM(Ref) const FUniqueNetIdRepl &A, const FUniqueNetIdRepl &B);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "NotEqual (Byte)", CompactNodeTitle = "!=", Keywords = "!= not equal"))
	static bool CompareNotEqualily(UPARAM(Ref) const FUniqueNetIdRepl &A, const FUniqueNetIdRepl &B);
};