#include "BP_FuncrionLibrary.h"

#include "BP_OnlineSessionSearchResult.h"

FString UBP_FuncrionLibrary::GetSessionName(const FBP_OnlineSessionSearchResult &SessionSearch) {
	FString name;
	SessionSearch.data.Session.SessionSettings.Get(FName("Name"), name);
	return name;
}