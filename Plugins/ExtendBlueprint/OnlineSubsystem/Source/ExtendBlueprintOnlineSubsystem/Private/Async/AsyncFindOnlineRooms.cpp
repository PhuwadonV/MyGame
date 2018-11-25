#include "AsyncFindOnlineRooms.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

#if WITH_EDITOR
#include "Engine.h"
#endif

UAsyncFindOnlineRooms* UAsyncFindOnlineRooms::FindOnlineRooms(APlayerController *PlayerController, FName OnlineSubsystem, UOnlineSessionSearchWrapper *SessionSearch) {
	UAsyncFindOnlineRooms *asyncFindOnlineRooms = NewObject<UAsyncFindOnlineRooms>();

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
			asyncFindOnlineRooms->OnlineSession = onlineSessionPtr.Get();
		}
		else {
			asyncFindOnlineRooms->bIsFailed = true;
			return asyncFindOnlineRooms;
		}
	}
	else {
		asyncFindOnlineRooms->bIsFailed = true;
		return asyncFindOnlineRooms;
	}

	asyncFindOnlineRooms->PlayerId = PlayerController->PlayerState->UniqueId.GetUniqueNetId();

	if (!asyncFindOnlineRooms->PlayerId.IsValid()) {
#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Invalid Player ID"));
#endif
		asyncFindOnlineRooms->bIsFailed = true;
		return asyncFindOnlineRooms;
	}

	if (SessionSearch != nullptr) {
		asyncFindOnlineRooms->SessionSearch = MakeShareable(new FOnlineSessionSearch{ SessionSearch->data });
	}
	else {
		asyncFindOnlineRooms->SessionSearch = MakeShareable(new FOnlineSessionSearch{});
		auto& sessionSearch = asyncFindOnlineRooms->SessionSearch;
		sessionSearch->bIsLanQuery = false;
		sessionSearch->PingBucketSize = 50;
		sessionSearch->MaxSearchResults = 100;
	}

	return asyncFindOnlineRooms;
}

void UAsyncFindOnlineRooms::Activate() {
	if (bIsFailed) return;
	TArray<UOnlineSessionSearchResultWrapper*> results;

	FOnFindSessionsCompleteDelegate onFindSessionsComplete = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UAsyncFindOnlineRooms::OnComplete);

	DelegateHandle = OnlineSession->AddOnFindSessionsCompleteDelegate_Handle(onFindSessionsComplete);

	OnlineSession->FindSessions(*PlayerId, SessionSearch.ToSharedRef());
}

void UAsyncFindOnlineRooms::OnComplete(bool bWasSuccessful) {
	TArray<UOnlineSessionSearchResultWrapper*> results;
	
	if (bWasSuccessful) {
		for (int32 i = 0; i < SessionSearch->SearchResults.Num(); i++)
		{
			UOnlineSessionSearchResultWrapper *result = NewObject<UOnlineSessionSearchResultWrapper>();
			result->data = SessionSearch->SearchResults[i];
			results.Add(result);
		}

		OnSuccess.Broadcast(results);
	}
	else {
		OnFailure.Broadcast(results);
	}
}