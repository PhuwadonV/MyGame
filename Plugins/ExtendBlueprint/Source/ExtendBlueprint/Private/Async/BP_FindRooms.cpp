#include "BP_FindRooms.h"

#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

UBP_FindRooms* UBP_FindRooms::FindRooms(APlayerController *PlayerController, bool bIsLAN, int32 MaxSearchResults, bool bIsPresence) {
	UBP_FindRooms *findRooms = NewObject<UBP_FindRooms>();
	findRooms->PlayerId = PlayerController->GetLocalPlayer()->GetPreferredUniqueNetId();

	auto& SessionSearch = findRooms->SessionSearch;
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = bIsLAN;
	SessionSearch->MaxSearchResults = MaxSearchResults;
	SessionSearch->PingBucketSize = 50;

	if (bIsPresence)
	{
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, bIsPresence, EOnlineComparisonOp::Equals);
	}

	return findRooms;
}

void UBP_FindRooms::Activate() {
	if (!PlayerId.IsValid()) return;

	IOnlineSessionPtr onlineSessionPtr = IOnlineSubsystem::Get()->GetSessionInterface();
	if (!onlineSessionPtr.IsValid()) return;
	IOnlineSession *onlineSession = onlineSessionPtr.Get();

	FOnFindSessionsCompleteDelegate onFindSessionsComplete = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UBP_FindRooms::OnComplete);

	TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SessionSearch.ToSharedRef();

	DelegateHandle = onlineSession->AddOnFindSessionsCompleteDelegate_Handle(onFindSessionsComplete);
	onlineSession->FindSessions(*PlayerId, SearchSettingsRef);
}

void UBP_FindRooms::OnComplete(bool bWasSuccessful) {
	IOnlineSession *onlineSession = IOnlineSubsystem::Get()->GetSessionInterface().Get();
	onlineSession->ClearOnFindSessionsCompleteDelegate_Handle(DelegateHandle);

	TArray<FBP_OnlineSessionSearchResult> results;
	
	if (bWasSuccessful) {
		for (int32 i = 0; i < SessionSearch->SearchResults.Num(); i++)
		{
			FBP_OnlineSessionSearchResult result;
			result.data = SessionSearch->SearchResults[i];
			results.Add(result);
		}

		OnSuccess.Broadcast(results);
	}
	else {
		OnFailure.Broadcast(results);
	}
}