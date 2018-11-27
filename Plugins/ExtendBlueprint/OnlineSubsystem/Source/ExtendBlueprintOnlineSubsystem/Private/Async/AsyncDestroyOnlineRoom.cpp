#include "AsyncDestroyOnlineRoom.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

UAsyncDestroyOnlineRoom* UAsyncDestroyOnlineRoom::DestroyOnlineRoom(FName OnlineSubsystem, EOnlineSessionType SessionType) {
	UAsyncDestroyOnlineRoom *AsyncDestroyOnlineRoom = NewObject<UAsyncDestroyOnlineRoom>();

	IOnlineSubsystem *OnlineSubsystemInterface;
	if (OnlineSubsystem == NAME_None) {
		OnlineSubsystemInterface = IOnlineSubsystem::Get();
	}
	else {
		OnlineSubsystemInterface = IOnlineSubsystem::Get(OnlineSubsystem);
	}

	if (OnlineSubsystemInterface != nullptr) {
		IOnlineSessionPtr OnlineSessionPtr = OnlineSubsystemInterface->GetSessionInterface();
		if (OnlineSessionPtr.IsValid()) {
			AsyncDestroyOnlineRoom->OnlineSession = OnlineSessionPtr.Get();
		}
		else {
			AsyncDestroyOnlineRoom->bIsFailed = true;
			return AsyncDestroyOnlineRoom;
		}
	}
	else {
		AsyncDestroyOnlineRoom->bIsFailed = true;
		return AsyncDestroyOnlineRoom;
	}

	AsyncDestroyOnlineRoom->SessionType = SessionType;

	return AsyncDestroyOnlineRoom;
}

void UAsyncDestroyOnlineRoom::Activate() {
	if (bIsFailed) return;

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::CreateUObject(this, &UAsyncDestroyOnlineRoom::OnComplete);

	switch (SessionType) {
	case EOnlineSessionType::Game:
		OnlineSession->DestroySession(GameSessionName, OnDestroySessionCompleteDelegate);
		break;
	case EOnlineSessionType::Party:
		OnlineSession->DestroySession(PartySessionName, OnDestroySessionCompleteDelegate);
		break;
	}

	OnCompleteDelegateHandle = OnDestroySessionCompleteDelegate.GetHandle();
}

void UAsyncDestroyOnlineRoom::OnComplete(FName SessionName, bool bWasSuccessful) {
	OnlineSession->ClearOnDestroySessionCompleteDelegate_Handle(OnCompleteDelegateHandle);

	if (bWasSuccessful) {
		OnSuccess.Broadcast();
	}
	else {
		OnFailure.Broadcast();
	}
}