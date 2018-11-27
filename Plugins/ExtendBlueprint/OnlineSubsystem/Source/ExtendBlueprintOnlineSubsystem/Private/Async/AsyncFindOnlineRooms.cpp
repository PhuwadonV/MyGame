#include "AsyncFindOnlineRooms.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"

#if WITH_EDITOR
#include "Engine.h"
#endif

UAsyncFindOnlineRooms* UAsyncFindOnlineRooms::FindOnlineRooms(APlayerController *PlayerController, FName OnlineSubsystem, UOnlineSessionSearchWrapper *SessionSearch) {
	UAsyncFindOnlineRooms *AsyncFindOnlineRooms = NewObject<UAsyncFindOnlineRooms>();

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
			AsyncFindOnlineRooms->OnlineSession = OnlineSessionPtr.Get();
		}
		else {
			AsyncFindOnlineRooms->bIsFailed = true;
			return AsyncFindOnlineRooms;
		}
	}
	else {
		AsyncFindOnlineRooms->bIsFailed = true;
		return AsyncFindOnlineRooms;
	}

	AsyncFindOnlineRooms->PlayerId = PlayerController->PlayerState->UniqueId.GetUniqueNetId();

	if (!AsyncFindOnlineRooms->PlayerId.IsValid()) {
#if WITH_EDITOR
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Invalid Player ID"));
#endif
		AsyncFindOnlineRooms->bIsFailed = true;
		return AsyncFindOnlineRooms;
	}

	if (SessionSearch != nullptr) {
		AsyncFindOnlineRooms->SessionSearch = MakeShareable(new FOnlineSessionSearch{ SessionSearch->Data });
	}
	else {
		AsyncFindOnlineRooms->SessionSearch = MakeShareable(new FOnlineSessionSearch{});
		auto& Search = AsyncFindOnlineRooms->SessionSearch;
		Search->bIsLanQuery = false;
		Search->PingBucketSize = 50;
		Search->MaxSearchResults = 100;
	}

	return AsyncFindOnlineRooms;
}

void UAsyncFindOnlineRooms::Activate() {
	if (bIsFailed) return;

	FOnFindSessionsCompleteDelegate onFindSessionsComplete = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UAsyncFindOnlineRooms::OnComplete);

	OnCompleteDelegateHandle = OnlineSession->AddOnFindSessionsCompleteDelegate_Handle(onFindSessionsComplete);

	OnlineSession->FindSessions(*PlayerId, SessionSearch.ToSharedRef());
}

void UAsyncFindOnlineRooms::OnComplete(bool bWasSuccessful) {
	if (bWasSuccessful) {
		for (int32 i = 0; i < SessionSearch->SearchResults.Num(); i++)
		{
			FBlueprintSessionResult BlueprintSessionResult;
			BlueprintSessionResult.OnlineResult = SessionSearch->SearchResults[i];
			BlueprintSessionResults.Add(BlueprintSessionResult);
		}

		OnSuccess.Broadcast(BlueprintSessionResults);
	}
	else {
		OnFailure.Broadcast(BlueprintSessionResults);
	}
}