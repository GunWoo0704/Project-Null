#include "StopwatchWidget.h"
#include "StopwatchManager.h"  // 싱글톤 매니저 추가
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UStopwatchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// `BP_Scorescreen`에서 기록된 시간을 불러와 표시
	if (TimerText)
	{
		FString TimeString = GetRecordedTimesAsString();
		UE_LOG(LogTemp, Warning, TEXT("Setting TimerText: %s"), *TimeString);
		TimerText->SetText(FText::FromString(TimeString));
	}
}

void UStopwatchWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UStopwatchWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	// 다른 StopwatchWidget이 표시되면 스톱워치 중지
	if (IsAnotherStopwatchWidgetVisible())
	{
		if (bIsRunning)
		{
			StopStopwatch();
		}
	}
	else if (IsVisible() && !bIsRunning)
	{
		StartStopwatch();
	}
}

bool UStopwatchWidget::IsAnotherStopwatchWidgetVisible()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UStopwatchWidget::StaticClass(), false);

	for (UUserWidget* Widget : FoundWidgets)
	{
		if (Widget != this && Widget->IsVisible())
		{
			return true;
		}
	}
	return false;
}

void UStopwatchWidget::StartStopwatch()
{
	if (!bIsRunning)
	{
		bIsRunning = true;
		PreviousTickTime = GetWorld()->GetTimeSeconds();

		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(StopwatchTimerHandle, this, &UStopwatchWidget::UpdateStopwatch, 0.05f, true);
		}
	}
}

void UStopwatchWidget::StopStopwatch()
{
	if (bIsRunning)
	{
		bIsRunning = false;
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().ClearTimer(StopwatchTimerHandle);
		}

		//  멈춘 시간 저장
		LastRecordedTime = ElapsedTime;
		RecordedTimes.Add(LastRecordedTime);
	}
}


void UStopwatchWidget::ResetStopwatch()
{
	StopStopwatch();
	ElapsedTime = 0.0f;

	// 싱글톤에서도 기록 초기화
	UStopwatchManager::GetInstance()->ClearRecordedTimes();

	if (TimerText)
	{
		TimerText->SetText(FText::FromString(TEXT("00:00.0")));
	}
}

FString UStopwatchWidget::GetRecordedTimesAsString()
{
	// 싱글톤에서 저장된 시간 반환
	return UStopwatchManager::GetInstance()->GetRecordedTimesAsString();
}

void UStopwatchWidget::UpdateStopwatch()
{
	if (bIsRunning)
	{
		float CurrentTime = GetWorld()->GetTimeSeconds();
		float DeltaTime = CurrentTime - PreviousTickTime;
		PreviousTickTime = CurrentTime;
		ElapsedTime += DeltaTime;

		int32 Minutes = FMath::FloorToInt(ElapsedTime / 60);
		int32 Seconds = FMath::FloorToInt(FMath::Fmod(ElapsedTime, 60));
		int32 Milliseconds = FMath::FloorToInt(FMath::Fmod(ElapsedTime, 1) * 100);

		if (!TimerText)
		{
			UE_LOG(LogTemp, Error, TEXT("TimerText is NULL in UpdateStopwatch!"));
			return;
		}

		FString TimeString = FString::Printf(TEXT("%02d:%02d.%02d"), Minutes, Seconds, Milliseconds);
		TimerText->SetText(FText::FromString(TimeString));
	}
}


