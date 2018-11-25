#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "OnlineSessionSettingsWrapper.h"
#include "OnlineSessionSearchResultWrapper.generated.h"

UCLASS(BlueprintType)
class UOnlineSessionSearchResultWrapper : public UObject {
	GENERATED_BODY()
public:
	FOnlineSessionSearchResult data;

	UFUNCTION(BlueprintPure)
	UOnlineSessionSettingsWrapper* GetOnlineSessionSettingsWrapper() const;
};