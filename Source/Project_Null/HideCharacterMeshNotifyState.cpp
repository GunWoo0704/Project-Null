#include "HideCharacterMeshNotifyState.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

void UHideCharacterMeshNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp)
	{
		// 캐릭터 메시와 모든 자손을 보이지 않게 설정
		SetMeshVisibilityRecursively(MeshComp, false);
	}
}

void UHideCharacterMeshNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp)
	{
		// 캐릭터 메시와 모든 자손을 다시 보이게 설정
		SetMeshVisibilityRecursively(MeshComp, true);
	}
}

void UHideCharacterMeshNotifyState::SetMeshVisibilityRecursively(USceneComponent* Component, bool bVisible)
{
	if (!Component)
	{
		return;
	}

	// 메시 보이기/숨기기 설정
	Component->SetVisibility(bVisible, true);

	// 자식 컴포넌트에 대해 재귀 호출하여 모두 설정
	for (USceneComponent* ChildComponent : Component->GetAttachChildren())
	{
		SetMeshVisibilityRecursively(ChildComponent, bVisible);
	}
}
