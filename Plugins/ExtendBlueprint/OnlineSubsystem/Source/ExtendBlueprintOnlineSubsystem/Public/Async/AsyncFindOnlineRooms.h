#pragma once

#include "ExtendBlueprintOnlineSubsystemBase.h"
#include "OnlineSessionSearchResultWrapper.h"
#include "OnlineSessionSearchWrapper.h"
#include "AsyncFindOnlineRooms.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncFindOnlineRoomsOutPin, const TArray<UOnlineSessionSearchResultWrapper*>&, Results);

UCLASS()
class UAsyncFindOnlineRooms : public UOnlineBlueprintCallProxyBase {
	GENERATED_BODY()
private:
	bool bIsFailed;
	IOnlineSession *OnlineSession;
	TSharedPtr<const FUniqueNetId> PlayerId;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	FDelegateHandle DelegateHandle;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncFindOnlineRooms* FindOnlineRooms(UPARAM() APlayerController *PlayerController, FName OnlineSubsystem, UOnlineSessionSearchWrapper *SessionSearch);

	UPROPERTY(BlueprintAssignable)
	FAsyncFindOnlineRoomsOutPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAsyncFindOnlineRoomsOutPin OnFailure;
	
	virtual void Activate() override;

	void OnComplete(bool bWasSuccessful);
};
