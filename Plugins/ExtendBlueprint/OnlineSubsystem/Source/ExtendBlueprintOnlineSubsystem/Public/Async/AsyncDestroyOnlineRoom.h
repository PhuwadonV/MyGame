#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "AsyncDestroyOnlineRoom.generated.h"

UCLASS()
class UAsyncDestroyOnlineRoom : public UOnlineBlueprintCallProxyBase {
	GENERATED_BODY()
private:
	bool bIsFailed;
	IOnlineSession *OnlineSession;
	EOnlineSessionType SessionType;
	FDelegateHandle OnCompleteDelegateHandle;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncDestroyOnlineRoom* DestroyOnlineRoom(FName OnlineSubsystem, EOnlineSessionType SessionType);

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;
	
	virtual void Activate() override;

	void OnComplete(FName SessionName, bool bWasSuccessful);
};
