#pragma once

#include "CoreMinimal.h"

#include "OnlineSessionSettings.h"

#include "BP_OnlineSessionSearchResult.generated.h"

USTRUCT(BlueprintType)
struct FBP_OnlineSessionSearchResult {
	GENERATED_BODY()
public:
	FOnlineSessionSearchResult data;
};