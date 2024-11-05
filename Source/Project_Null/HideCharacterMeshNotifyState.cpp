#include "HideCharacterMeshNotifyState.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

void UHideCharacterMeshNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp)
	{
		// ĳ���� �޽ÿ� ��� �ڼ��� ������ �ʰ� ����
		SetMeshVisibilityRecursively(MeshComp, false);
	}
}

void UHideCharacterMeshNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp)
	{
		// ĳ���� �޽ÿ� ��� �ڼ��� �ٽ� ���̰� ����
		SetMeshVisibilityRecursively(MeshComp, true);
	}
}

void UHideCharacterMeshNotifyState::SetMeshVisibilityRecursively(USceneComponent* Component, bool bVisible)
{
	if (!Component)
	{
		return;
	}

	// �޽� ���̱�/����� ����
	Component->SetVisibility(bVisible, true);

	// �ڽ� ������Ʈ�� ���� ��� ȣ���Ͽ� ��� ����
	for (USceneComponent* ChildComponent : Component->GetAttachChildren())
	{
		SetMeshVisibilityRecursively(ChildComponent, bVisible);
	}
}
