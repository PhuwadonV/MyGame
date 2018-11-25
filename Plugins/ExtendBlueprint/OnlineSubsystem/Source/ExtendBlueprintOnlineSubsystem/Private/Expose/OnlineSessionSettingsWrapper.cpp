#include "OnlineSessionSettingsWrapper.h"

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::CreateOnlineSessionSettingsWrapper() {
	return NewObject<UOnlineSessionSettingsWrapper>();
}

UOnlineSessionSettingsWrapper::UOnlineSessionSettingsWrapper(const FObjectInitializer &ObjectInitlizer) :
	Super(ObjectInitlizer) {
	data.bAllowInvites = true;
	data.bAllowJoinInProgress = true;
	data.bAllowJoinViaPresence = true;
	data.bAllowJoinViaPresenceFriendsOnly = false;
	data.bAntiCheatProtected = false;
	data.bIsDedicated = false;
	data.bIsLANMatch = false;
	data.bShouldAdvertise = true;
	data.bUsesPresence = false;
	data.bUsesStats = false;
	data.NumPrivateConnections = 0;
	data.NumPublicConnections = 10;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAllowInvites(bool bAllowInvites) {
	data.bAllowInvites = bAllowInvites;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAllowJoinInProgress(bool bAllowJoinInProgress) {
	data.bAllowJoinInProgress = bAllowJoinInProgress;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAllowJoinViaPresence(bool bAllowJoinViaPresence) {
	data.bAllowJoinViaPresence = bAllowJoinViaPresence;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAllowJoinViaPresenceFriendsOnly(bool bAllowJoinViaPresenceFriendsOnly) {
	data.bAllowJoinViaPresenceFriendsOnly = bAllowJoinViaPresenceFriendsOnly;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAntiCheatProtected(bool bAntiCheatProtected) {
	data.bAntiCheatProtected = bAntiCheatProtected;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetIsDedicated(bool bIsDedicated) {
	data.bIsDedicated = bIsDedicated;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetBuildUniqueId(int32 BuildUniqueId) {
	data.BuildUniqueId = BuildUniqueId;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetIsLANMatch(bool bIsLANMatch) {
	data.bIsLANMatch = bIsLANMatch;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetShouldAdvertise(bool bShouldAdvertise) {
	data.bShouldAdvertise = bShouldAdvertise;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetUsesPresence(bool bUsesPresence) {
	data.bUsesPresence = bUsesPresence;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetUsesStats(bool bUsesStats) {
	data.bUsesStats = bUsesStats;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetNumPublicConnections(int32 NumPublicConnections) {
	data.NumPublicConnections = NumPublicConnections;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetNumPrivateConnections(int32 NumPrivateConnections) {
	data.NumPrivateConnections = NumPrivateConnections;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAsString(FName Key, FString Value, EOnlineDataAdvertisementTypeWrapper AdvertisementType) {
	data.Set(Key, Value, static_cast<EOnlineDataAdvertisementType::Type>(*reinterpret_cast<uint8*>(&AdvertisementType)));
	return this;
}

void UOnlineSessionSettingsWrapper::GetAsString(FName Key, bool &isSuccess, FString &Value) const {
	isSuccess = data.Get(Key, Value);
}

void UOnlineSessionSettingsWrapper::GetAsInteger(FName Key, bool &isSuccess, int32 &Value) const {
	isSuccess = data.Get(Key, Value);
}