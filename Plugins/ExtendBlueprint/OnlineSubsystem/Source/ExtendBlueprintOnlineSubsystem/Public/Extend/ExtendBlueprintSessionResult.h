#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "FindSessionsCallbackProxy.h"
#include "OnlineSessionSettingsWrapper.h"
#include "ExtendBlueprintSessionResult.generated.h"

UCLASS()
class UExtendBlueprintSessionResult : public UObject {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static UOnlineSessionSettingsWrapper* GetOnlineSessionSettingsWrapper(UPARAM(Ref) const FBlueprintSessionResult &Session);
};