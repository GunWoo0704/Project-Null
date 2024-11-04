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
	// ����ũ�� ī�޶� ����ũ Ŭ���� ���� (�𸮾� �����Ϳ��� ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraShake")
	float ShakeScale = 1.0f; // ����ũ ���� ����

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	// ī�޶� ����ũ �ν��Ͻ��� �����ϱ� ���� ���� ������
	TWeakObjectPtr<UCameraShakeBase> ActiveCameraShake;
};
