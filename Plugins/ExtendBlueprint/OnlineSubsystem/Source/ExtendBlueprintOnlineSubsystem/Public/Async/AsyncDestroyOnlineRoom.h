#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "AsyncDestroyOnlineRoom.generated.h"

UCLASS()
class UAsyncDestroyOnlineRoom : public UOnlineBlueprintCallProxyBase {
	GENERATED_BODY()
private:
	bool bIsFailed;
	IOnlineSession *OnlineSession;
	ESessionType SessionType;
	FDelegateHandle DelegateHandle;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncDestroyOnlineRoom* DestroyOnlineRoom(FName OnlineSubsystem, ESessionType SessionType);

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEmptyOnlineDelegate OnFailure;
	
	virtual void Activate() override;

	void OnComplete(FName SessionName, bool bWasSuccessful);
};
