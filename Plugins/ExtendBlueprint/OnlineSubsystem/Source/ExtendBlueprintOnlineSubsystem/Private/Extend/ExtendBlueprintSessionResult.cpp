#include "ExtendBlueprintSessionResult.h"

UOnlineSessionSettingsWrapper* UExtendBlueprintSessionResult::GetOnlineSessionSettingsWrapper(const FBlueprintSessionResult &Session) {
	UOnlineSessionSettingsWrapper *OnlineSessionSettingsWrapper = NewObject<UOnlineSessionSettingsWrapper>();
	OnlineSessionSettingsWrapper->Data = Session.OnlineResult.Session.SessionSettings;
	return OnlineSessionSettingsWrapper;
}