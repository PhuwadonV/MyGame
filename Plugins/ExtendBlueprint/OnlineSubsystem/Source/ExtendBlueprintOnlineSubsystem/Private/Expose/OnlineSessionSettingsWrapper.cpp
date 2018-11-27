#include "OnlineSessionSettingsWrapper.h"

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::CreateOnlineSessionSettingsWrapper() {
	return NewObject<UOnlineSessionSettingsWrapper>();
}

UOnlineSessionSettingsWrapper::UOnlineSessionSettingsWrapper(const FObjectInitializer &ObjectInitlizer) :
	Super(ObjectInitlizer) {
	Data.bAllowInvites = true;
	Data.bAllowJoinInProgress = true;
	Data.bAllowJoinViaPresence = true;
	Data.bAllowJoinViaPresenceFriendsOnly = false;
	Data.bAntiCheatProtected = false;
	Data.bIsDedicated = false;
	Data.bIsLANMatch = false;
	Data.bShouldAdvertise = true;
	Data.bUsesPresence = false;
	Data.bUsesStats = false;
	Data.NumPrivateConnections = 0;
	Data.NumPublicConnections = 10;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAllowInvites(bool bAllowInvites) {
	Data.bAllowInvites = bAllowInvites;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAllowJoinInProgress(bool bAllowJoinInProgress) {
	Data.bAllowJoinInProgress = bAllowJoinInProgress;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAllowJoinViaPresence(bool bAllowJoinViaPresence) {
	Data.bAllowJoinViaPresence = bAllowJoinViaPresence;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAllowJoinViaPresenceFriendsOnly(bool bAllowJoinViaPresenceFriendsOnly) {
	Data.bAllowJoinViaPresenceFriendsOnly = bAllowJoinViaPresenceFriendsOnly;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAntiCheatProtected(bool bAntiCheatProtected) {
	Data.bAntiCheatProtected = bAntiCheatProtected;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetIsDedicated(bool bIsDedicated) {
	Data.bIsDedicated = bIsDedicated;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetBuildUniqueId(int32 BuildUniqueId) {
	Data.BuildUniqueId = BuildUniqueId;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetIsLANMatch(bool bIsLANMatch) {
	Data.bIsLANMatch = bIsLANMatch;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetShouldAdvertise(bool bShouldAdvertise) {
	Data.bShouldAdvertise = bShouldAdvertise;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetUsesPresence(bool bUsesPresence) {
	Data.bUsesPresence = bUsesPresence;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetUsesStats(bool bUsesStats) {
	Data.bUsesStats = bUsesStats;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetNumPublicConnections(int32 NumPublicConnections) {
	Data.NumPublicConnections = NumPublicConnections;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetNumPrivateConnections(int32 NumPrivateConnections) {
	Data.NumPrivateConnections = NumPrivateConnections;
	return this;
}

UOnlineSessionSettingsWrapper* UOnlineSessionSettingsWrapper::SetAsString(FName Key, FString Value, EOnlineDataAdvertisementTypeWrapper AdvertisementType) {
	Data.Set(Key, Value, static_cast<EOnlineDataAdvertisementType::Type>(*reinterpret_cast<uint8*>(&AdvertisementType)));
	return this;
}

void UOnlineSessionSettingsWrapper::GetAsString(FName Key, FString &Value, EOnlineSessionCustomSettingStatus &OnlineSessionCustomSettingStatus) {
	if (Data.Get(Key, Value)) {
		OnlineSessionCustomSettingStatus = EOnlineSessionCustomSettingStatus::Succeed;
	}
	else {
		OnlineSessionCustomSettingStatus = EOnlineSessionCustomSettingStatus::Failed;
	}
}