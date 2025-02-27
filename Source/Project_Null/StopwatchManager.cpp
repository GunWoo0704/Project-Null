#include "StopwatchManager.h"

UStopwatchManager* UStopwatchManager::Instance = nullptr;

UStopwatchManager* UStopwatchManager::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<UStopwatchManager>();
		Instance->AddToRoot();  // GC(Garbage Collector)에서 보호
	}
	return Instance;
}

void UStopwatchManager::AddRecordedTime(float Time)
{
	RecordedTimes.Add(Time);
}

void UStopwatchManager::ClearRecordedTimes()
{
	RecordedTimes.Empty();
}

FString UStopwatchManager::GetRecordedTimesAsString() const
{
	FString Result;
	for (float Time : RecordedTimes)
	{
		int32 Minutes = FMath::FloorToInt(Time / 60);
		int32 Seconds = FMath::FloorToInt(FMath::Fmod(Time, 60));
		int32 Milliseconds = FMath::FloorToInt(FMath::Fmod(Time, 1) * 100);
		Result += FString::Printf(TEXT("%02d:%02d.%02d\n"), Minutes, Seconds, Milliseconds);
	}
	return Result;
}
