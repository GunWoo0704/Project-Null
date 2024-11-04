#include "HideMeshNotifyState.h"
#include "GameFramework/Actor.h"

void UHideMeshNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		// 메시 숨김
		MeshComp->SetVisibility(false);
	}
}

void UHideMeshNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		// 메시 다시 보이게 설정
		MeshComp->SetVisibility(true);
	}
}
