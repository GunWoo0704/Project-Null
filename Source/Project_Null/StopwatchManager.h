#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StopwatchManager.generated.h"

UCLASS()
class PROJECT_NULL_API UStopwatchManager : public UObject
{
	GENERATED_BODY()

public:
	static UStopwatchManager* GetInstance();

	void AddRecordedTime(float Time);
	void ClearRecordedTimes();
	FString GetRecordedTimesAsString() const;

private:
	static UStopwatchManager* Instance;
	UPROPERTY()
	TArray<float> RecordedTimes;
};
