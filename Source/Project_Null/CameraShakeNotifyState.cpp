#include "CameraShakeNotifyState.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"

void UCameraShakeNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (CameraShakeClass && MeshComp)
	{
		UWorld* World = MeshComp->GetWorld();
		if (World)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
			if (PlayerController)
			{
				// ī�޶� ����ũ ����
				PlayerController->ClientStartCameraShake(CameraShakeClass, ShakeScale);
			}
		}
	}
}

void UCameraShakeNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (CameraShakeClass && MeshComp)
	{
		UWorld* World = MeshComp->GetWorld();
		if (World)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
			if (PlayerController)
			{
				// ī�޶� ����ũ ����
				PlayerController->ClientStopCameraShake(CameraShakeClass, false);
			}
		}
	}
}
