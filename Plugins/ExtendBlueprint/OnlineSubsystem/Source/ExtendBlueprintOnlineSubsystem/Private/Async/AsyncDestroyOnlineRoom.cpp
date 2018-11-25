#include "AsyncDestroyOnlineRoom.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

UAsyncDestroyOnlineRoom* UAsyncDestroyOnlineRoom::DestroyOnlineRoom(FName OnlineSubsystem, ESessionType SessionType) {
	UAsyncDestroyOnlineRoom *asyncDestroyOnlineRoom = NewObject<UAsyncDestroyOnlineRoom>();

	IOnlineSubsystem *onlineSubsystem;
	if (OnlineSubsystem == NAME_None) {
		onlineSubsystem = IOnlineSubsystem::Get(OnlineSubsystem);
	}
	else {
		onlineSubsystem = IOnlineSubsystem::Get(OnlineSubsystem);
	}

	if (onlineSubsystem != nullptr) {
		IOnlineSessionPtr onlineSessionPtr = onlineSubsystem->GetSessionInterface();
		if (onlineSessionPtr.IsValid()) {
			asyncDestroyOnlineRoom->OnlineSession = onlineSessionPtr.Get();
		}
		else {
			asyncDestroyOnlineRoom->bIsFailed = true;
			return asyncDestroyOnlineRoom;
		}
	}
	else {
		asyncDestroyOnlineRoom->bIsFailed = true;
		return asyncDestroyOnlineRoom;
	}

	asyncDestroyOnlineRoom->SessionType = SessionType;

	return asyncDestroyOnlineRoom;
}

void UAsyncDestroyOnlineRoom::Activate() {
	if (bIsFailed) return;

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UAsyncDestroyOnlineRoom::OnComplete);

	switch (SessionType) {
	case ESessionType::Game:
		OnlineSession->DestroySession(GameSessionName, OnDestroySessionCompleteDelegate);
		break;
	case ESessionType::Party:
		OnlineSession->DestroySession(PartySessionName, OnDestroySessionCompleteDelegate);
		break;
	}

	DelegateHandle = OnDestroySessionCompleteDelegate.GetHandle();
}

void UAsyncDestroyOnlineRoom::OnComplete(FName SessionName, bool bWasSuccessful) {
	OnlineSession->ClearOnDestroySessionCompleteDelegate_Handle(DelegateHandle);

	if (bWasSuccessful) {
		OnSuccess.Broadcast();
	}
	else {
		OnFailure.Broadcast();
	}
}