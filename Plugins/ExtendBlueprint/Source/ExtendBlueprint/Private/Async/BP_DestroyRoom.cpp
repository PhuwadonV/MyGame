#include "BP_DestroyRoom.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

UBP_DestroyRoom* UBP_DestroyRoom::DestroyRoom( FName SessionName) {
	UBP_DestroyRoom *destroyRoom = NewObject<UBP_DestroyRoom>();
	destroyRoom->SessionName = SessionName;

	return destroyRoom;
}

void UBP_DestroyRoom::Activate() {
	IOnlineSessionPtr onlineSessionPtr = IOnlineSubsystem::Get()->GetSessionInterface();
	if (!onlineSessionPtr.IsValid()) return;
	IOnlineSession *onlineSession = onlineSessionPtr.Get();

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UBP_DestroyRoom::OnComplete);
	onlineSession->DestroySession(SessionName, OnDestroySessionCompleteDelegate);
	DelegateHandle = OnDestroySessionCompleteDelegate.GetHandle();
}

void UBP_DestroyRoom::OnComplete(FName SessionName, bool bWasSuccessful) {
	IOnlineSessionPtr onlineSessionPtr = IOnlineSubsystem::Get()->GetSessionInterface();
	IOnlineSession *onlineSession = onlineSessionPtr.Get();

	onlineSession->ClearOnDestroySessionCompleteDelegate_Handle(DelegateHandle);

	if (bWasSuccessful) {
		OnSuccess.Broadcast();
	}
	else {
		OnFailure.Broadcast();
	}
}