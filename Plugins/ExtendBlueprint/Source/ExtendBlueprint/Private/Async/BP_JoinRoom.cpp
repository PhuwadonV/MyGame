#include "BP_JoinRoom.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

UBP_JoinRoom* UBP_JoinRoom::JoinRoom(APlayerController *PlayerController, FName SessionName, const FBP_OnlineSessionSearchResult& Session) {
	UBP_JoinRoom *joinRoom = NewObject<UBP_JoinRoom>();
	joinRoom->PlayerId = PlayerController->GetLocalPlayer()->GetPreferredUniqueNetId();
	joinRoom->SessionName = SessionName;
	joinRoom->Session = Session;

	return joinRoom;
}

void UBP_JoinRoom::Activate() {
	if (!PlayerId.IsValid()) return;

	IOnlineSessionPtr onlineSessionPtr = IOnlineSubsystem::Get()->GetSessionInterface();
	if (!onlineSessionPtr.IsValid()) return;
	IOnlineSession *onlineSession = onlineSessionPtr.Get();

	FOnJoinSessionCompleteDelegate onJoinSessionComplete = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UBP_JoinRoom::OnComplete);
	DelegateHandle = onlineSession->AddOnJoinSessionCompleteDelegate_Handle(onJoinSessionComplete);

	onlineSession->JoinSession(*PlayerId, SessionName, Session.data);
}

void UBP_JoinRoom::OnComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) {
	IOnlineSession *onlineSession = IOnlineSubsystem::Get()->GetSessionInterface().Get();
	onlineSession->ClearOnJoinSessionCompleteDelegate_Handle(DelegateHandle);

	TArray<FBP_OnlineSessionSearchResult> results;

	if (Result == EOnJoinSessionCompleteResult::Success) {
		FString ServerUrl;
		onlineSession->GetResolvedConnectString(SessionName, ServerUrl);
		OnSuccess.Broadcast(ServerUrl);
	}
	else {
		OnFailure.Broadcast(FString(""));
	}
}