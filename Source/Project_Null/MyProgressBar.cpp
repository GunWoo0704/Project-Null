#include "MyProgressBar.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyProgressBar, Log, All);

void UMyProgressBar::StartProgress(float Duration)
{
	if (Duration == 3.2f && !bIsTimerActive1)
	{
		ProgressBar1->SetPercent(1.0f);
		StartTime1 = GetWorld()->GetTimeSeconds();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle1, this, &UMyProgressBar::UpdateProgress1, 0.05f, true);
		bIsTimerActive1 = true;
	}
	else if (Duration == 10.0f && !bIsTimerActive2)
	{
		ProgressBar2->SetPercent(1.0f);
		StartTime2 = GetWorld()->GetTimeSeconds();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &UMyProgressBar::UpdateProgress2, 0.05f, true);
		bIsTimerActive2 = true;
	}
	else if (Duration == 30.0f && !bIsTimerActive3)
	{
		ProgressBar3->SetPercent(1.0f);
		StartTime3 = GetWorld()->GetTimeSeconds();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle3, this, &UMyProgressBar::UpdateProgress3, 0.05f, true);
		bIsTimerActive3 = true;
	}
}

void UMyProgressBar::UpdateProgress1()
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	float ElapsedTime = CurrentTime - StartTime1;
	float NewPercent = 1.0f - (ElapsedTime / 3.2f);

	UE_LOG(LogMyProgressBar, Log, TEXT("Progress Bar 1 - Elapsed Time: %f, New Percent: %f"), ElapsedTime, NewPercent);

	if (ElapsedTime >= 3.2f)
	{
		NewPercent = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle1);
		bIsTimerActive1 = false;
	}

	ProgressBar1->SetPercent(FMath::Clamp(NewPercent, 0.0f, 1.0f));
}

void UMyProgressBar::UpdateProgress2()
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	float ElapsedTime = CurrentTime - StartTime2;
	float NewPercent = 1.0f - (ElapsedTime / 10.0f);

	UE_LOG(LogMyProgressBar, Log, TEXT("Progress Bar 2 - Elapsed Time: %f, New Percent: %f"), ElapsedTime, NewPercent);

	if (ElapsedTime >= 10.0f)
	{
		NewPercent = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle2);
		bIsTimerActive2 = false;
	}

	ProgressBar2->SetPercent(FMath::Clamp(NewPercent, 0.0f, 1.0f));
}

void UMyProgressBar::UpdateProgress3()
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	float ElapsedTime = CurrentTime - StartTime3;
	float NewPercent = 1.0f - (ElapsedTime / 30.0f);

	UE_LOG(LogMyProgressBar, Log, TEXT("Progress Bar 3 - Elapsed Time: %f, New Percent: %f"), ElapsedTime, NewPercent);

	if (ElapsedTime >= 30.0f)
	{
		NewPercent = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle3);
		bIsTimerActive3 = false;
	}

	ProgressBar3->SetPercent(FMath::Clamp(NewPercent, 0.0f, 1.0f));
}

// 낙하 상태 변경
void UMyProgressBar::SetFallingState(bool bFalling)
{
	bIsFalling = bFalling;
	UpdateImageState();
}

// 이미지 상태 업데이트
void UMyProgressBar::UpdateImageState()
{
	if (FallingImage && NormalImage && GroundImage && AirImage)
	{
		if (bIsFalling)
		{
			FallingImage->SetVisibility(ESlateVisibility::Visible);
			NormalImage->SetVisibility(ESlateVisibility::Hidden);
			AirImage->SetVisibility(ESlateVisibility::Visible);
			GroundImage->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			FallingImage->SetVisibility(ESlateVisibility::Hidden);
			NormalImage->SetVisibility(ESlateVisibility::Visible);
			AirImage->SetVisibility(ESlateVisibility::Hidden);
			GroundImage->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
