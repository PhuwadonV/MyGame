#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "GameFramework/OnlineReplStructs.h"
#include "GameFramework/PlayerController.h"
#include "OnlineSessionSettings.h"
#include "BP_OnlineSessionSearchResult.h"

#include "BP_FindRooms.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBP_FindRoomsOutPin, const TArray<FBP_OnlineSessionSearchResult>&, Results);

UCLASS()
class EXTENDBLUEPRINT_API UBP_FindRooms : public UBlueprintAsyncActionBase {
	GENERATED_BODY()
private:
	FUniqueNetIdRepl PlayerId;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	FDelegateHandle DelegateHandle;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (BlueprintInternalUseOnly = "true"))
	static UBP_FindRooms* FindRooms(UPARAM() APlayerController *PlayerController, bool bIsLAN, int32 MaxSearchResults, bool bIsPresence);

	UPROPERTY(BlueprintAssignable)
	FBP_FindRoomsOutPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FBP_FindRoomsOutPin OnFailure;
	
	virtual void Activate() override;

	void OnComplete(bool bWasSuccessful);
};
