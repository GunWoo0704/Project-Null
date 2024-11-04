#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CameraShakeNotifyState.generated.h"
#pragma once

UCLASS()
class PROJECT_NULL_API UCameraShakeNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// 셰이크할 카메라 셰이크 클래스 지정 (언리얼 에디터에서 설정 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	float ShakeScale = 1.0f; // 셰이크 강도 조절

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	// 카메라 셰이크 인스턴스를 저장하기 위한 약한 포인터
	TWeakObjectPtr<UCameraShakeBase> ActiveCameraShake;
};
