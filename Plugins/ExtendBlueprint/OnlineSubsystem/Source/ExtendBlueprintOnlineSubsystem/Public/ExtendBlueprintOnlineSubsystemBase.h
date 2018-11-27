#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameSession.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

UENUM(BlueprintType)
enum class EOnlineComparisonOpWrapper : uint8 {
	Equals            = EOnlineComparisonOp::Equals,
	NotEquals         = EOnlineComparisonOp::NotEquals,
	GreaterThan       = EOnlineComparisonOp::GreaterThan,
	GreaterThanEquals = EOnlineComparisonOp::GreaterThanEquals,
	LessThan          = EOnlineComparisonOp::LessThan,
	LessThanEquals    = EOnlineComparisonOp::LessThanEquals,
	Near              = EOnlineComparisonOp::Near,
	In                = EOnlineComparisonOp::In,
	NotIn             = EOnlineComparisonOp::NotIn
};

UENUM(BlueprintType)
enum class EOnlineDataAdvertisementTypeWrapper : uint8 {
	DontAdvertise           = EOnlineDataAdvertisementType::DontAdvertise,
	ViaOnlineService        = EOnlineDataAdvertisementType::ViaOnlineService,
	ViaOnlineServiceAndPing = EOnlineDataAdvertisementType::ViaOnlineServiceAndPing,
	ViaPingOnly             = EOnlineDataAdvertisementType::ViaPingOnly
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