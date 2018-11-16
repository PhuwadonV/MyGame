#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "OnlineSessionInterface.h"

#include "BP_DestroyRoom.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBP_DestroyRoomOutPin);

UCLASS()
class EXTENDBLUEPRINT_API UBP_DestroyRoom : public UBlueprintAsyncActionBase {
	GENERATED_BODY()
private:
	FName SessionName;
	FDelegateHandle DelegateHandle;
public:
	UFUNCTION(BlueprintCallable, Category = "Online|Session", Meta = (BlueprintInternalUseOnly = "true"))
	static UBP_DestroyRoom* DestroyRoom(FName SessionName);

	UPROPERTY(BlueprintAssignable)
	FBP_DestroyRoomOutPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FBP_DestroyRoomOutPin OnFailure;
	
	virtual void Activate() override;

	void OnComplete(FName SessionName, bool bWasSuccessful);
};
