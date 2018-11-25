#pragma once

#include "ExtendBlueprintEngineBase.h"
#include "AsyncExecBase.h"
#include "AsyncTryExecBase.generated.h"

UCLASS()
class UAsyncTryExecBase : public UBlueprintAsyncActionBase {
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FAsyncExecOutPin OnSuccess;
	
	UPROPERTY(BlueprintAssignable)
	FAsyncExecOutPin OnFailure;
};