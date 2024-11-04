#include "HideMeshNotifyState.h"
#include "GameFramework/Actor.h"

void UHideMeshNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		// �޽� ����
		MeshComp->SetVisibility(false);
	}
}

void UHideMeshNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		// �޽� �ٽ� ���̰� ����
		MeshComp->SetVisibility(true);
	}
}
