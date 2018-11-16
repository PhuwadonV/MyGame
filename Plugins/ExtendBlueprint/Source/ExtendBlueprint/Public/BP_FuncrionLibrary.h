#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "BP_OnlineSessionSearchResult.h"

#include "BP_FuncrionLibrary.generated.h"

UCLASS()
class EXTENDBLUEPRINT_API UBP_FuncrionLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Online|Session")
	static FString GetSessionName(UPARAM() const FBP_OnlineSessionSearchResult &SessionSearch);
};