#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "FindSessionsCallbackProxy.h"
#include "OnlineSessionSettingsWrapper.h"
#include "ExtendBlueprintOnlineSubsystemFunctions.generated.h"

UCLASS()
class UExtendBlueprintOnlineSubsystemFunctions : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static UOnlineSessionSettingsWrapper* GetOnlineSessionSettingsWrapper(UPARAM(Ref) const FBlueprintSessionResult &Session);
};