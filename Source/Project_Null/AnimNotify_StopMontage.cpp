// StopMontageNotify.cpp

#include "AnimNotify_StopMontage.h" // ��� ���� �̸��� �����ϰ� ����
#include "GameFramework/Actor.h"
#include "Animation/AnimInstance.h"

void UAnimNotify_StopMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetAnimInstance())
	{
		MeshComp->GetAnimInstance()->Montage_Stop(0.2f); // 0.2f�� ���̵� �ƿ� �ð��Դϴ�. �ʿ信 ���� �����ϼ���.
	}
}
