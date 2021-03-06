#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/OnlineReplStructs.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameSession.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

UENUM(BlueprintType)
enum class EOnlineDataAdvertisementTypeWrapper : uint8 {
	DontAdvertise,
	ViaOnlineService,
	ViaOnlineServiceAndPing,
	ViaPingOnly
};

UENUM(BlueprintType)
enum class EOnlineSessionType : uint8
{
	Game,
	Party
};

UENUM()
enum class EOnlineSessionCustomSettingStatus : uint8
{
	Succeed,
	Failed
};