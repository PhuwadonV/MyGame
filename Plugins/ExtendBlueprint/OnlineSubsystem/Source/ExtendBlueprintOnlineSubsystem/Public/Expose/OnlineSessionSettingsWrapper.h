#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "OnlineSessionSettingsWrapper.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UOnlineSessionSettingsWrapper : public UObject {
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session")
	static UOnlineSessionSettingsWrapper* CreateOnlineSessionSettingsWrapper();

	FOnlineSessionSettings data;

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

	UFUNCTION(BlueprintPure)
	void GetAsString(FName Key, bool &IsSuccess, FString &Value) const;

	UFUNCTION(BlueprintPure)
	void GetAsInteger(FName Key, bool &IsSuccess, int32 &Value) const;
};