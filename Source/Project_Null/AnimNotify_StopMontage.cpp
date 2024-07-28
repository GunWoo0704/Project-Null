// StopMontageNotify.cpp

#include "AnimNotify_StopMontage.h" // 헤더 파일 이름과 동일하게 수정
#include "GameFramework/Actor.h"
#include "Animation/AnimInstance.h"

void UAnimNotify_StopMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetAnimInstance())
	{
		MeshComp->GetAnimInstance()->Montage_Stop(0.2f); // 0.2f는 페이드 아웃 시간입니다. 필요에 따라 조정하세요.
	}
}
