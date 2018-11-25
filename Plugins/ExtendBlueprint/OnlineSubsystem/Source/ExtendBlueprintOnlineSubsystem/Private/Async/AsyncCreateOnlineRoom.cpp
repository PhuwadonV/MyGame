#include "AsyncCreateOnlineRoom.h"
#include "GameFramework/PlayerState.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

#if WITH_EDITOR
#include "Engine.h"
#endif

UAsyncCreateOnlineRoom* UAsyncCreateOnlineRoom::CreateOnlineRoom(APlayerController *PlayerController, FName OnlineSubsystem, const UOnlineSessionSettingsWrapper *Setting, ESessionType SessionType) {
	UAsyncCreateOnlineRoom *asyncCreateOnlineRoom = NewObject<UAsyncCreateOnlineRoom>();

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
			asyncCreateOnlineRoom->OnlineSession = onlineSessionPtr.Get();
		}
		else {
			asyncCreateOnlineRoom->bIsFailed = true;
			return asyncCreateOnlineRoom;
		}
	}
	else {
		asyncCreateOnlineRoom->bIsFailed = true;
		return asyncCreateOnlineRoom;
	}

	asyncCreateOnlineRoom->PlayerId = PlayerController->PlayerState->UniqueId.GetUniqueNetId();

	if (!asyncCreateOnlineRoom->PlayerId.IsValid()) {
#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Invalid Player ID"));
#endif
		asyncCreateOnlineRoom->bIsFailed = true;
		return asyncCreateOnlineRoom;
	}

	if (Setting != nullptr) {
		asyncCreateOnlineRoom->OnlineSessionSettingsWrapper = Setting;
	}
	else {
		asyncCreateOnlineRoom->OnlineSessionSettingsWrapper = UOnlineSessionSettingsWrapper::CreateOnlineSessionSettingsWrapper();
	}

	asyncCreateOnlineRoom->SessionType = SessionType;

	return asyncCreateOnlineRoom;
}

void UAsyncCreateOnlineRoom::Activate() {
	if (bIsFailed) return;

	DelegateHandle = OnlineSession->AddOnCreateSessionCompleteDelegate_Handle(
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &UAsyncCreateOnlineRoom::OnCreateSessionComplete));

	switch (SessionType) {
	case ESessionType::Game:
		OnlineSession->CreateSession(*PlayerId, GameSessionName, OnlineSessionSettingsWrapper->data);
		break;
	case ESessionType::Party:
		OnlineSession->CreateSession(*PlayerId, PartySessionName, OnlineSessionSettingsWrapper->data);
		break;
	}
}

void UAsyncCreateOnlineRoom::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) {
	OnlineSession->ClearOnCreateSessionCompleteDelegate_Handle(DelegateHandle);

	if (bWasSuccessful) {
		DelegateHandle = OnlineSession->AddOnStartSessionCompleteDelegate_Handle(
			FOnCreateSessionCompleteDelegate::CreateUObject(this, &UAsyncCreateOnlineRoom::OnStartSessionComplete));

		OnlineSession->StartSession(SessionName);
	}
	else {
		OnFailure.Broadcast();
	}
}

void UAsyncCreateOnlineRoom::OnStartSessionComplete(FName SessionName, bool bWasSuccessful) {
	OnlineSession->ClearOnStartSessionCompleteDelegate_Handle(DelegateHandle);

	if (bWasSuccessful) {
		OnSuccess.Broadcast();
	}
	else {
		OnFailure.Broadcast();
	}
}