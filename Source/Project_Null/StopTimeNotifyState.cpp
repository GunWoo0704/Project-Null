#include "StopTimeNotifyState.h" // �̸� ���濡 ���� ���� ��� ����
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h" // TActorIterator ��� �� �ʿ��� ���

void UStopTimeNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	UWorld* World = MeshComp->GetWorld();
	if (!World) return;

	// ĳ���͸� ������ ��� ������ Custom Time Dilation�� 0���� ����
	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor && Actor != MeshComp->GetOwner()) // ĳ���� ����
		{
			Actor->CustomTimeDilation = 0.0f; // �ð� ���߱�
		}
	}
}

void UStopTimeNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	UWorld* World = MeshComp->GetWorld();
	if (!World) return;

	// ĳ���͸� ������ ��� ������ Custom Time Dilation�� 1�� ����
	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor && Actor != MeshComp->GetOwner()) // ĳ���� ����
		{
			Actor->CustomTimeDilation = 1.0f; // �ð� ����
		}
	}
}
