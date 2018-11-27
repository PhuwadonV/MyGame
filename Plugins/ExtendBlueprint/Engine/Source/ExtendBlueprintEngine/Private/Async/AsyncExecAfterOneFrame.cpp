#include "AsyncExecAfterOneFrame.h"
#include "UObject/Object.h"

UAsyncExecAfterOneFrame* UAsyncExecAfterOneFrame::ExecAfterOneFrame(const UObject* WorldContextObject) {
	UAsyncExecAfterOneFrame *AsyncWaitForOneFrame = NewObject<UAsyncExecAfterOneFrame>();
	AsyncWaitForOneFrame->WorldContextObject = WorldContextObject;
	return AsyncWaitForOneFrame;
}

void UAsyncExecAfterOneFrame::Activate() {
	WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick([this]() { Exec.Broadcast(); });
}