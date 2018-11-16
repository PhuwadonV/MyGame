#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "GameFramework/OnlineReplStructs.h"
#include "GameFramework/PlayerController.h"
#include "OnlineSessionInterface.h"
#include "BP_OnlineSessionSearchResult.h"

#include "BP_JoinRoom.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBP_JoinRoomOutPin, FString, ServerURL);

UCLASS()
class EXTENDBLUEPRINT_API UBP_JoinRoom : public UBlueprintAsyncActionBase {
	GENERATED_BODY()
private:
	FUniqueNetIdRepl PlayerId;
	FName SessionName;
	FBP_OnlineSessionSearchResult Session;
	FDelegateHandle DelegateHandle;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", meta = (BlueprintInternalUseOnly = "true"))
	static UBP_JoinRoom* JoinRoom(UPARAM() APlayerController *PlayerController, FName SessionName, const FBP_OnlineSessionSearchResult& Session);

	UPROPERTY(BlueprintAssignable)
	FBP_JoinRoomOutPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FBP_JoinRoomOutPin OnFailure;

	virtual void Activate() override;

	void OnComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};