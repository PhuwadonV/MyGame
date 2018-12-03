#include "ExtendBlueprintOnlineSubsystemFunctions.h"

UOnlineSessionSettingsWrapper* UExtendBlueprintOnlineSubsystemFunctions::GetOnlineSessionSettingsWrapper(const FBlueprintSessionResult &Session) {
	UOnlineSessionSettingsWrapper *OnlineSessionSettingsWrapper = NewObject<UOnlineSessionSettingsWrapper>();
	OnlineSessionSettingsWrapper->Data = Session.OnlineResult.Session.SessionSettings;
	return OnlineSessionSettingsWrapper;
}