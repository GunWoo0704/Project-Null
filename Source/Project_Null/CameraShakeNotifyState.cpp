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
				// 카메라 셰이크 시작
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
				// 카메라 셰이크 종료
				PlayerController->ClientStopCameraShake(CameraShakeClass, false);
			}
		}
	}
}
