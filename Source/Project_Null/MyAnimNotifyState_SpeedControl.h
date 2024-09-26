#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyAnimNotifyState_SpeedControl.generated.h"

UCLASS(meta = (DisplayName = "Speed Control Notify State"))
class PROJECT_NULL_API UMyAnimNotifyState_SpeedControl : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// 디테일 창에서 수정 가능한 속도 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
	float TargetSpeed = 600.0f;

	// 오버라이드 함수
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
