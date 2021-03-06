#include "AsyncCreateOnlineRoom.h"
#include "GameFramework/PlayerState.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

#if !UE_BUILD_SHIPPING
#include "Engine.h"
#endif

UAsyncCreateOnlineRoom* UAsyncCreateOnlineRoom::CreateOnlineRoom(APlayerController *PlayerController, FName OnlineSubsystem, const UOnlineSessionSettingsWrapper *Setting, EOnlineSessionType SessionType) {
	UAsyncCreateOnlineRoom *AsyncCreateOnlineRoom = NewObject<UAsyncCreateOnlineRoom>();

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
			AsyncCreateOnlineRoom->OnlineSession = OnlineSessionPtr.Get();
		}
		else {
			AsyncCreateOnlineRoom->bIsFailed = true;
			return AsyncCreateOnlineRoom;
		}
	}
	else {
		AsyncCreateOnlineRoom->bIsFailed = true;
		return AsyncCreateOnlineRoom;
	}

	AsyncCreateOnlineRoom->PlayerId = PlayerController->PlayerState->UniqueId.GetUniqueNetId();

	if (!AsyncCreateOnlineRoom->PlayerId.IsValid()) {
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Invalid Player ID"));
#endif
		AsyncCreateOnlineRoom->bIsFailed = true;
		return AsyncCreateOnlineRoom;
	}

	if (Setting != nullptr) {
		AsyncCreateOnlineRoom->OnlineSessionSettingsWrapper = Setting;
	}
	else {
		AsyncCreateOnlineRoom->OnlineSessionSettingsWrapper = UOnlineSessionSettingsWrapper::CreateOnlineSessionSettingsWrapper();
	}

	AsyncCreateOnlineRoom->SessionType = SessionType;

	return AsyncCreateOnlineRoom;
}

void UAsyncCreateOnlineRoom::Activate() {
	if (bIsFailed) {
		OnFailure.Broadcast();
		return;
	}

	OnCompleteDelegateHandle = OnlineSession->AddOnCreateSessionCompleteDelegate_Handle(
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &UAsyncCreateOnlineRoom::OnCreateSessionComplete));

	switch (SessionType) {
	case EOnlineSessionType::Game:
		OnlineSession->CreateSession(*PlayerId, GameSessionName, OnlineSessionSettingsWrapper->Data);
		break;
	case EOnlineSessionType::Party:
		OnlineSession->CreateSession(*PlayerId, PartySessionName, OnlineSessionSettingsWrapper->Data);
		break;
	}
}

void UAsyncCreateOnlineRoom::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) {
	OnlineSession->ClearOnCreateSessionCompleteDelegate_Handle(OnCompleteDelegateHandle);

	if (bWasSuccessful) {
		OnCompleteDelegateHandle = OnlineSession->AddOnStartSessionCompleteDelegate_Handle(
			FOnCreateSessionCompleteDelegate::CreateUObject(this, &UAsyncCreateOnlineRoom::OnStartSessionComplete));

		OnlineSession->StartSession(SessionName);
	}
	else {
		OnFailure.Broadcast();
	}
}

void UAsyncCreateOnlineRoom::OnStartSessionComplete(FName SessionName, bool bWasSuccessful) {
	OnlineSession->ClearOnStartSessionCompleteDelegate_Handle(OnCompleteDelegateHandle);

	if (bWasSuccessful) {
#if !UE_BUILD_SHIPPING
		FString SessionUrl;
		OnlineSession->GetResolvedConnectString(SessionName, SessionUrl);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Session URL : %s"), *SessionUrl));
#endif
		OnSuccess.Broadcast();
	}
	else {
		OnFailure.Broadcast();
	}
}