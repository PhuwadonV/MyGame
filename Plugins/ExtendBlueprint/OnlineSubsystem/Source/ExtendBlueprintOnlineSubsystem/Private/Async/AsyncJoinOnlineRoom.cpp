#include "AsyncJoinOnlineRoom.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

#if WITH_EDITOR
#include "Engine.h"
#endif

UAsyncJoinOnlineRoom* UAsyncJoinOnlineRoom::JoinOnlineRoom(APlayerController *PlayerController, FName OnlineSubsystem, const UOnlineSessionSearchResultWrapper *Session, ESessionType SessionType) {
	UAsyncJoinOnlineRoom *asyncJoinOnlineRoom = NewObject<UAsyncJoinOnlineRoom>();

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
			asyncJoinOnlineRoom->OnlineSession = onlineSessionPtr.Get();
		}
		else {
			asyncJoinOnlineRoom->bIsFailed = true;
			return asyncJoinOnlineRoom;
		}
	}
	else {
		asyncJoinOnlineRoom->bIsFailed = true;
		return asyncJoinOnlineRoom;
	}

	asyncJoinOnlineRoom->PlayerId = PlayerController->PlayerState->UniqueId.GetUniqueNetId();

	if (!asyncJoinOnlineRoom->PlayerId.IsValid()) {
#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Invalid Player ID"));
#endif
		asyncJoinOnlineRoom->bIsFailed = true;
		return asyncJoinOnlineRoom;
	}

	asyncJoinOnlineRoom->SessionType = SessionType;
	asyncJoinOnlineRoom->OnlineSessionSearchResultWrapper = Session;

	return asyncJoinOnlineRoom;
}

void UAsyncJoinOnlineRoom::Activate() {
	if (bIsFailed) return;

	FOnJoinSessionCompleteDelegate onJoinSessionComplete = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UAsyncJoinOnlineRoom::OnComplete);
	DelegateHandle = OnlineSession->AddOnJoinSessionCompleteDelegate_Handle(onJoinSessionComplete);

	switch (SessionType) {
	case ESessionType::Game:
		OnlineSession->JoinSession(*PlayerId, GameSessionName, OnlineSessionSearchResultWrapper->data);
		break;
	case ESessionType::Party:
		OnlineSession->JoinSession(*PlayerId, PartySessionName, OnlineSessionSearchResultWrapper->data);
		break;
	}
}

void UAsyncJoinOnlineRoom::OnComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) {
	TArray<UOnlineSessionSearchResultWrapper*> results;

	if (Result == EOnJoinSessionCompleteResult::Success) {
		FString ServerUrl;
		OnlineSession->GetResolvedConnectString(SessionName, ServerUrl);
		OnSuccess.Broadcast(ServerUrl);
	}
	else {
		OnFailure.Broadcast(FString());
	}
}