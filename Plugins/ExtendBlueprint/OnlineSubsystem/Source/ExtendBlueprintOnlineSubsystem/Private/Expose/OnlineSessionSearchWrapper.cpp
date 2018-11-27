#include "OnlineSessionSearchWrapper.h"
#include "OnlineSubsystemTypes.h"

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::CreateOnlineSessionSearchWrapper() {
	return NewObject<UOnlineSessionSearchWrapper>();
}

UOnlineSessionSearchWrapper::UOnlineSessionSearchWrapper(const FObjectInitializer &ObjectInitlizer) :
	Super(ObjectInitlizer) {
	Data.bIsLanQuery = false;
	Data.MaxSearchResults = 100;
	Data.PingBucketSize = 50;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetIsLanQuery(bool bIsLanQuery) {
	Data.bIsLanQuery = bIsLanQuery;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetMaxSearchResults(int32 MaxSearchResults) {
	Data.MaxSearchResults = MaxSearchResults;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetPingBucketSize(int32 PingBucketSize) {
	Data.PingBucketSize = PingBucketSize;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetPlatformHash(bool PlatformHash) {
	Data.PlatformHash = PlatformHash;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetTimeoutInSeconds(bool TimeoutInSeconds) {
	Data.TimeoutInSeconds = TimeoutInSeconds;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetIsPresence(bool bIsPresence) {
	Data.QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetQueryString(FName Key, FString Value, EOnlineComparisonOpWrapper CompareOp) {
	Data.QuerySettings.Set(Key, Value, static_cast<EOnlineComparisonOp::Type>(*reinterpret_cast<uint8*>(&CompareOp)));
	return this;
}