#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "GameFramework/OnlineReplStructs.h"
#include "OnlineSessionSettingsWrapper.h"
#include "AsyncCreateOnlineRoom.generated.h"

UCLASS()
class UAsyncCreateOnlineRoom : public UOnlineBlueprintCallProxyBase {
	GENERATED_BODY()
private:
	bool bIsFailed;
	IOnlineSession *OnlineSession;
	TSharedPtr<const FUniqueNetId> PlayerId;
	ESessionType SessionType;
	FDelegateHandle DelegateHandle;
	
	UPROPERTY()
	const UOnlineSessionSettingsWrapper *OnlineSessionSettingsWrapper;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncCreateOnlineRoom* CreateOnlineRoom(UPARAM() APlayerController *PlayerController, FName OnlineSubsystem, const UOnlineSessionSettingsWrapper *Setting, ESessionType SessionType);

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;
	
	virtual void Activate() override;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
};
