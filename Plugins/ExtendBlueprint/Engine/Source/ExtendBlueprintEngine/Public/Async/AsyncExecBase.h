#pragma once

#include "ExtendBlueprintEngineBase.h"
#include "AsyncExecBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncExecOutPin);

UCLASS()
class UAsyncExecBase : public UBlueprintAsyncActionBase {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FAsyncExecOutPin Exec;
};