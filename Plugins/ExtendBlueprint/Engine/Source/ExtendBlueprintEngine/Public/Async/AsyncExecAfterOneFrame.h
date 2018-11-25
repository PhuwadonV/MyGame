#pragma once

#include "ExtendBlueprintEngineBase.h"
#include "AsyncExecBase.h"
#include "AsyncExecAfterOneFrame.generated.h"

UCLASS()
class UAsyncExecAfterOneFrame : public UAsyncExecBase {
	GENERATED_BODY()
private:
	const UObject *WorldContextObject;
public:
	UFUNCTION(BlueprintCallable, Category = "Async", Meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"))
	static UAsyncExecAfterOneFrame* ExecAfterOneFrame(const UObject* WorldContextObject);

	virtual void Activate() override;
};
