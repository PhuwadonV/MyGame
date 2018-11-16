#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/PlayerController.h"
#include "BP_PlayerController.generated.h"

UCLASS()
class UBP_PlayerController : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Networking")
	static void ClientTravel(UPARAM() APlayerController *PlayerController, const FString & URL, enum ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid);
};