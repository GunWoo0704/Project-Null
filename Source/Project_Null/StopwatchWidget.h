#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "StopwatchWidget.generated.h"

UCLASS()
class PROJECT_NULL_API UStopwatchWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Stopwatch")
	void StartStopwatch();

	UFUNCTION(BlueprintCallable, Category = "Stopwatch")
	void StopStopwatch();

	UFUNCTION(BlueprintCallable, Category = "Stopwatch")
	void ResetStopwatch();

	UFUNCTION(BlueprintCallable, Category = "Stopwatch")
	FString GetRecordedTimesAsString(); // 저장된 시간 리스트를 문자열로 변환

	UPROPERTY(BlueprintReadWrite, Category = "Stopwatch")
	float LastRecordedTime = 0.0f; //  LastRecordedTime을 public으로 선언

	UPROPERTY(BlueprintReadWrite, Category = "Stopwatch")
	TArray<float> RecordedTimes; // 여러 번 멈춘 시간을 저장

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Stopwatch")
	UTextBlock* TimerText;

private:
	void UpdateStopwatch();
	bool IsAnotherStopwatchWidgetVisible(); // 다른 StopWatch 위젯이 있는지 확인

	FTimerHandle StopwatchTimerHandle;
	float ElapsedTime = 0.0f;
	bool bIsRunning = false;
	float PreviousTickTime = 0.0f;
};
