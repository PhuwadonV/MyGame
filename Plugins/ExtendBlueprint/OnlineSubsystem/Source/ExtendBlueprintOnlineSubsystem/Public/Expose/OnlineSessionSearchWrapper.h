#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "OnlineSessionSearchWrapper.generated.h"

UCLASS(BlueprintType)
class UOnlineSessionSearchWrapper : public UObject {
	GENERATED_UCLASS_BODY()
public:
	FOnlineSessionSearch Data;

	UFUNCTION(BlueprintCallable, Category = "Online|Session")
	static UOnlineSessionSearchWrapper* CreateOnlineSessionSearchWrapper();

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSearchWrapper* SetIsLanQuery(bool bIsLanQuery);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSearchWrapper* SetMaxSearchResults(int32 MaxSearchResults);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSearchWrapper* SetPingBucketSize(int32 PingBucketSize);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSearchWrapper* SetPlatformHash(bool PlatformHash);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSearchWrapper* SetTimeoutInSeconds(bool TimeoutInSeconds);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSearchWrapper* SetIsPresence(bool bIsPresence);
};