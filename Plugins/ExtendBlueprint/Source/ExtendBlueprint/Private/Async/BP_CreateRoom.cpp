#include "BP_CreateRoom.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

#if WITH_EDITOR
#include "Engine.h"
#endif

UBP_CreateRoom* UBP_CreateRoom::CreateRoom(APlayerController *PlayerController, FString RoomName, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers) {
	UBP_CreateRoom *createRoom = NewObject<UBP_CreateRoom>();
	createRoom->RoomName = RoomName;
	createRoom->PlayerId = PlayerController->GetLocalPlayer()->GetPreferredUniqueNetId();
	createRoom->SessionName = SessionName;
	createRoom->bIsLAN = bIsLAN;
	createRoom->bIsPresence = bIsPresence;
	createRoom->MaxNumPlayers = MaxNumPlayers;

	return createRoom;
}

void UBP_CreateRoom::Activate() {
	if (!PlayerId.IsValid()) {
#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Invalid Player ID"));
#endif
		return;
	}

	IOnlineSessionPtr onlineSessionPtr = IOnlineSubsystem::Get()->GetSessionInterface();
	if (!onlineSessionPtr.IsValid()) return;
	IOnlineSession *onlineSession = onlineSessionPtr.Get();

	TSharedRef<FOnlineSessionSettings> sessionSettings = MakeShareable(new FOnlineSessionSettings());
	sessionSettings->bIsLANMatch = bIsLAN;
	sessionSettings->bUsesPresence = bIsPresence;
	sessionSettings->NumPublicConnections = MaxNumPlayers;
	sessionSettings->NumPrivateConnections = 0;
	sessionSettings->bAllowInvites = true;
	sessionSettings->bAllowJoinInProgress = true;
	sessionSettings->bShouldAdvertise = true;
	sessionSettings->bAllowJoinViaPresence = true;
	sessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

	sessionSettings->Set(FName("Name"), RoomName, EOnlineDataAdvertisementType::ViaOnlineService);

	DelegateHandle = onlineSession->AddOnCreateSessionCompleteDelegate_Handle(
		FOnCreateSessionCompleteDelegate::CreateUObject(this, &UBP_CreateRoom::OnCreateSessionComplete));

	onlineSession->CreateSession(*PlayerId, SessionName, *sessionSettings);
}

void UBP_CreateRoom::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) {
	IOnlineSessionPtr onlineSessionPtr = IOnlineSubsystem::Get()->GetSessionInterface();
	IOnlineSession *onlineSession = onlineSessionPtr.Get();

	onlineSession->ClearOnCreateSessionCompleteDelegate_Handle(DelegateHandle);

	if (bWasSuccessful) {
		DelegateHandle = onlineSession->AddOnStartSessionCompleteDelegate_Handle(
			FOnCreateSessionCompleteDelegate::CreateUObject(this, &UBP_CreateRoom::OnStartSessionComplete));

		onlineSession->StartSession(SessionName);
	}
	else {
		OnFailure.Broadcast();
	}
}

void UBP_CreateRoom::OnStartSessionComplete(FName SessionName, bool bWasSuccessful) {
	IOnlineSessionPtr onlineSessionPtr = IOnlineSubsystem::Get()->GetSessionInterface();
	IOnlineSession *onlineSession = onlineSessionPtr.Get();

	onlineSession->ClearOnStartSessionCompleteDelegate_Handle(DelegateHandle);

	if (bWasSuccessful) {
		OnSuccess.Broadcast();
	}
	else {
		OnFailure.Broadcast();
	}
}