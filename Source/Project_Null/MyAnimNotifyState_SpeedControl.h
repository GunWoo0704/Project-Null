#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyAnimNotifyState_SpeedControl.generated.h"

UCLASS(meta = (DisplayName = "Speed Control Notify State"))
class PROJECT_NULL_API UMyAnimNotifyState_SpeedControl : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// ������ â���� ���� ������ �ӵ� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Control")
	float TargetSpeed = 600.0f;

	// �������̵� �Լ�
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
