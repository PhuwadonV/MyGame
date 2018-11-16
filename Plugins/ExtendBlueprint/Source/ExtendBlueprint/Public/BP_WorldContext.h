#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "CoreUObject.h"

#include "BP_WorldContext.generated.h"

UCLASS()
class EXTENDBLUEPRINT_API UBP_WorldContext : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Networking", meta = (WorldContext = "WorldContextObject"))
	static bool ServerTravel(const UObject *WorldContextObject, const FString &URL, bool Absolute, bool ShouldSkipGameNotify);
};