#include "AsyncJoinOnlineRoom.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

#if !UE_BUILD_SHIPPING
#include "Engine.h"
#endif

UAsyncJoinOnlineRoom* UAsyncJoinOnlineRoom::JoinOnlineRoom(APlayerController *PlayerController, FName OnlineSubsystem, const FBlueprintSessionResult &Session, EOnlineSessionType SessionType) {
	UAsyncJoinOnlineRoom *AsyncJoinOnlineRoom = NewObject<UAsyncJoinOnlineRoom>();

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
			AsyncJoinOnlineRoom->OnlineSession = OnlineSessionPtr.Get();
		}
		else {
			AsyncJoinOnlineRoom->bIsFailed = true;
			return AsyncJoinOnlineRoom;
		}
	}
	else {
		AsyncJoinOnlineRoom->bIsFailed = true;
		return AsyncJoinOnlineRoom;
	}

	AsyncJoinOnlineRoom->PlayerId = PlayerController->PlayerState->UniqueId.GetUniqueNetId();

	if (!AsyncJoinOnlineRoom->PlayerId.IsValid()) {
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Invalid Player ID"));
#endif
		AsyncJoinOnlineRoom->bIsFailed = true;
		return AsyncJoinOnlineRoom;
	}

	AsyncJoinOnlineRoom->SessionType = SessionType;
	AsyncJoinOnlineRoom->OnlineSessionSearchResult = Session.OnlineResult;

	return AsyncJoinOnlineRoom;
}

void UAsyncJoinOnlineRoom::Activate() {
	if (bIsFailed) {
		OnFailure.Broadcast(FString());
		return;
	}

	FOnJoinSessionCompleteDelegate onJoinSessionComplete = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UAsyncJoinOnlineRoom::OnComplete);
	OnCompleteDelegateHandle = OnlineSession->AddOnJoinSessionCompleteDelegate_Handle(onJoinSessionComplete);

	switch (SessionType) {
	case EOnlineSessionType::Game:
		OnlineSession->JoinSession(*PlayerId, GameSessionName, OnlineSessionSearchResult);
		break;
	case EOnlineSessionType::Party:
		OnlineSession->JoinSession(*PlayerId, PartySessionName, OnlineSessionSearchResult);
		break;
	}
}

void UAsyncJoinOnlineRoom::OnComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) {
	OnlineSession->ClearOnJoinSessionCompleteDelegate_Handle(OnCompleteDelegateHandle);

	if (Result == EOnJoinSessionCompleteResult::Success) {
		FString SessionUrl;
		OnlineSession->GetResolvedConnectString(SessionName, SessionUrl);
		OnSuccess.Broadcast(SessionUrl);
	}
	else {
		OnFailure.Broadcast(FString());
	}
}