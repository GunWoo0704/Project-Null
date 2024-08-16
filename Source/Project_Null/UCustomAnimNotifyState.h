// UCustomAnimNotifyState.h

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UCustomAnimNotifyState.generated.h"

UCLASS()
class PROJECT_NULL_API UCustomAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// ��Ƽ���� ���� �� ȣ��
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	// ��Ƽ���� ���� �� ȣ��
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// ��Ƽ������ ��� ���̸� �����ϴ� ������Ƽ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Notify")
	float NotifyDuration;

private:
	// �÷��̾� �Է� �� �ִϸ��̼� ��� �����ϴ� �Լ�
	void DisableInputAndStopMontages(AActor* Actor, USkeletalMeshComponent* MeshComp);

	// �÷��̾� �Է� �� �ִϸ��̼� ��� �ٽ� Ȱ��ȭ�ϴ� �Լ�
	void EnableInputAndResumeMontages(AActor* Actor, USkeletalMeshComponent* MeshComp);
};
