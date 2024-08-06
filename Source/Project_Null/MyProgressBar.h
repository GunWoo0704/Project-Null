#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "MyProgressBar.generated.h"

UCLASS()
class PROJECT_NULL_API UMyProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Progress")
	void StartProgress(float Duration);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar1;  // 3.2초 동안 감소

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar2;  // 10초 동안 감소

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar3;  // 30초 동안 감소

	bool bIsTimerActive1;
	bool bIsTimerActive2;
	bool bIsTimerActive3;

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
};
