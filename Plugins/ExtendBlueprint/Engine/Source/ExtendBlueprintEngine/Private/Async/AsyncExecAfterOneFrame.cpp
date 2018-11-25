#include "AsyncExecAfterOneFrame.h"
#include "Engine/World.h"

UAsyncExecAfterOneFrame* UAsyncExecAfterOneFrame::ExecAfterOneFrame(const UObject* WorldContextObject) {
	UAsyncExecAfterOneFrame *asyncWaitForOneFrame = NewObject<UAsyncExecAfterOneFrame>();
	asyncWaitForOneFrame->WorldContextObject = WorldContextObject;
	return asyncWaitForOneFrame;
}

void UAsyncExecAfterOneFrame::Activate() {
	WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick([this]() { Exec.Broadcast(); });
}