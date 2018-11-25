#include "OnlineSessionSearchResultWrapper.h"

UOnlineSessionSettingsWrapper* UOnlineSessionSearchResultWrapper::GetOnlineSessionSettingsWrapper() const {
	UOnlineSessionSettingsWrapper *onlineSessionSettingsWrapper = NewObject<UOnlineSessionSettingsWrapper>();
	onlineSessionSettingsWrapper->data = data.Session.SessionSettings;
	return onlineSessionSettingsWrapper;
}