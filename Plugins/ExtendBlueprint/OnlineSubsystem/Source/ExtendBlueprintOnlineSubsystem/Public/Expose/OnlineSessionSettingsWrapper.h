#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "OnlineSessionSettingsWrapper.generated.h"

UCLASS(BlueprintType)
class UOnlineSessionSettingsWrapper : public UObject {
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session")
	static UOnlineSessionSettingsWrapper* CreateOnlineSessionSettingsWrapper();

	FOnlineSessionSettings Data;

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetAllowInvites(bool bAllowInvites);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetAllowJoinInProgress(bool bAllowJoinInProgress);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetAllowJoinViaPresence(bool bAllowJoinViaPresence);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetAllowJoinViaPresenceFriendsOnly(bool bAllowJoinViaPresenceFriendsOnly);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetAntiCheatProtected(bool bAntiCheatProtected);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetIsDedicated(bool bIsDedicated);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetBuildUniqueId(int32 BuildUniqueId);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetIsLANMatch(bool bIsLANMatch);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetShouldAdvertise(bool bShouldAdvertise);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetUsesPresence(bool bUsesPresence);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetUsesStats(bool bUsesStats);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetNumPublicConnections(int32 NumPublicConnections);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetNumPrivateConnections(int32 NumPrivateConnections);

	UFUNCTION(BlueprintCallable)
	UOnlineSessionSettingsWrapper* SetAsString(FName Key, FString Value, EOnlineDataAdvertisementTypeWrapper AdvertisementType);
	
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "OnlineSessionCustomSettingStatus"))
	void GetAsString(FName Key, FString &Value, EOnlineSessionCustomSettingStatus &OnlineSessionCustomSettingStatus);
};