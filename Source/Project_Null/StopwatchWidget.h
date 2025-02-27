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
	FString GetRecordedTimesAsString(); // ����� �ð� ����Ʈ�� ���ڿ��� ��ȯ

	UPROPERTY(BlueprintReadWrite, Category = "Stopwatch")
	float LastRecordedTime = 0.0f; //  LastRecordedTime�� public���� ����

	UPROPERTY(BlueprintReadWrite, Category = "Stopwatch")
	TArray<float> RecordedTimes; // ���� �� ���� �ð��� ����

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Stopwatch")
	UTextBlock* TimerText;

private:
	void UpdateStopwatch();
	bool IsAnotherStopwatchWidgetVisible(); // �ٸ� StopWatch ������ �ִ��� Ȯ��

	FTimerHandle StopwatchTimerHandle;
	float ElapsedTime = 0.0f;
	bool bIsRunning = false;
	float PreviousTickTime = 0.0f;
};
