#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "MyProgressBar.generated.h"

UCLASS()
class PROJECT_NULL_API UMyProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Progress")
	void StartProgress(float Duration);

	UFUNCTION(BlueprintCallable, Category = "State")
	void SetFallingState(bool bFalling); // 낙하 상태 변경

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar1;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar2;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar3;

	UPROPERTY(meta = (BindWidget))
	UImage* FallingImage;  // 낙하 중일 때 표시할 이미지

	UPROPERTY(meta = (BindWidget))
	UImage* NormalImage;  // 평상시 표시할 이미지

	UPROPERTY(meta = (BindWidget))
	UImage* GroundImage;  // 땅에 있을 때 표시할 이미지 (새로운 이미지)

	UPROPERTY(meta = (BindWidget))
	UImage* AirImage;  // 공중에 있을 때 표시할 이미지 (새로운 이미지)

	bool bIsTimerActive1;
	bool bIsTimerActive2;
	bool bIsTimerActive3;
	bool bIsFalling; // 낙하 상태를 저장하는 변수

private:
	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
	FTimerHandle TimerHandle3;

	float StartTime1;
	float StartTime2;
	float StartTime3;

	UFUNCTION()
	void UpdateProgress1();

	UFUNCTION()
	void UpdateProgress2();

	UFUNCTION()
	void UpdateProgress3();

	void UpdateImageState(); // 이미지 상태를 갱신하는 함수
};