#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "FindSessionsCallbackProxy.h"
#include "OnlineSessionSearchWrapper.h"
#include "AsyncFindOnlineRooms.generated.h"

UCLASS()
class UAsyncFindOnlineRooms : public UOnlineBlueprintCallProxyBase {
	GENERATED_BODY()
private:
	bool bIsFailed;
	IOnlineSession *OnlineSession;
	TSharedPtr<const FUniqueNetId> PlayerId;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	TArray<FBlueprintSessionResult> BlueprintSessionResults;
	FDelegateHandle OnCompleteDelegateHandle;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncFindOnlineRooms* FindOnlineRooms(UPARAM() APlayerController *PlayerController, FName OnlineSubsystem, UOnlineSessionSearchWrapper *SessionSearch);

	UPROPERTY(BlueprintAssignable)
	FBlueprintFindSessionsResultDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FBlueprintFindSessionsResultDelegate OnFailure;
	
	virtual void Activate() override;

	void OnComplete(bool bWasSuccessful);
};
