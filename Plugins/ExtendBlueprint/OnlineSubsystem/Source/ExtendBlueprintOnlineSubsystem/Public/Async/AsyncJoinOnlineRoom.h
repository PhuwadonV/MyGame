#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "OnlineSessionSearchResultWrapper.h"
#include "AsyncJoinOnlineRoom.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncJoinOnlineRoomOutPin, FString, SessionURL);

UCLASS()
class UAsyncJoinOnlineRoom : public UOnlineBlueprintCallProxyBase {
	GENERATED_BODY()
private:
	bool bIsFailed;
	IOnlineSession *OnlineSession;
	TSharedPtr<const FUniqueNetId> PlayerId;
	ESessionType SessionType;
	FDelegateHandle DelegateHandle;

	UPROPERTY()
	const UOnlineSessionSearchResultWrapper *OnlineSessionSearchResultWrapper;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncJoinOnlineRoom* JoinOnlineRoom(UPARAM() APlayerController *PlayerController, FName OnlineSubsystem, const UOnlineSessionSearchResultWrapper *Session, ESessionType SessionType);

	UPROPERTY(BlueprintAssignable)
	FAsyncJoinOnlineRoomOutPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAsyncJoinOnlineRoomOutPin OnFailure;

	virtual void Activate() override;

	void OnComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};