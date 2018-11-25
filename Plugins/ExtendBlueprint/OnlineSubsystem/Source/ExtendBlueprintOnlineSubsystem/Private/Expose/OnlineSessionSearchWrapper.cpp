#include "OnlineSessionSearchWrapper.h"
#include "OnlineSubsystemTypes.h"

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::CreateOnlineSessionSearchWrapper() {
	return NewObject<UOnlineSessionSearchWrapper>();
}

UOnlineSessionSearchWrapper::UOnlineSessionSearchWrapper(const FObjectInitializer &ObjectInitlizer) :
	Super(ObjectInitlizer) {
	data.bIsLanQuery = false;
	data.MaxSearchResults = 100;
	data.PingBucketSize = 50;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetIsLanQuery(bool bIsLanQuery) {
	data.bIsLanQuery = bIsLanQuery;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetMaxSearchResults(int32 MaxSearchResults) {
	data.MaxSearchResults = MaxSearchResults;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetPingBucketSize(int32 PingBucketSize) {
	data.PingBucketSize = PingBucketSize;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetPlatformHash(bool PlatformHash) {
	data.PlatformHash = PlatformHash;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetTimeoutInSeconds(bool TimeoutInSeconds) {
	data.TimeoutInSeconds = TimeoutInSeconds;
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetIsPresence(bool bIsPresence) {
	data.QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetQueryString(FName Key, FString Value, EOnlineComparisonOpWrapper CompareOp) {
	data.QuerySettings.Set(Key, Value, static_cast<EOnlineComparisonOp::Type>(*reinterpret_cast<uint8*>(&CompareOp)));
	return this;
}

UOnlineSessionSearchWrapper* UOnlineSessionSearchWrapper::SetQueryInteger(FName Key, int32 Value, EOnlineComparisonOpWrapper CompareOp) {
	data.QuerySettings.Set(Key, Value, static_cast<EOnlineComparisonOp::Type>(*reinterpret_cast<uint8*>(&CompareOp)));
	return this;
}