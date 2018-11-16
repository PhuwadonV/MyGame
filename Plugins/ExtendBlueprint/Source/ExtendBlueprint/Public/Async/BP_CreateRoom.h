#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "GameFramework/OnlineReplStructs.h"
#include "GameFramework/PlayerController.h"

#include "BP_CreateRoom.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBP_CreateRoomOutPin);

UCLASS()
class EXTENDBLUEPRINT_API UBP_CreateRoom : public UBlueprintAsyncActionBase {
	GENERATED_BODY()
private:
	FUniqueNetIdRepl PlayerId;
	FString RoomName;
	FName SessionName;
	bool bIsLAN;
	bool bIsPresence;
	int32 MaxNumPlayers;
	FDelegateHandle DelegateHandle;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (BlueprintInternalUseOnly = "true"))
	static UBP_CreateRoom* CreateRoom(UPARAM() APlayerController *PlayerController, FString RoomName, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	UPROPERTY(BlueprintAssignable)
	FBP_CreateRoomOutPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FBP_CreateRoomOutPin OnFailure;
	
	virtual void Activate() override;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
};
