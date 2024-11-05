#include "StopTimeNotifyState.h" // 이름 변경에 따른 파일 경로 수정
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h" // TActorIterator 사용 시 필요한 헤더

void UStopTimeNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	UWorld* World = MeshComp->GetWorld();
	if (!World) return;

	// 캐릭터를 제외한 모든 액터의 Custom Time Dilation을 0으로 설정
	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor && Actor != MeshComp->GetOwner()) // 캐릭터 제외
		{
			Actor->CustomTimeDilation = 0.0f; // 시간 멈추기
		}
	}
}

void UStopTimeNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	UWorld* World = MeshComp->GetWorld();
	if (!World) return;

	// 캐릭터를 제외한 모든 액터의 Custom Time Dilation을 1로 복원
	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor && Actor != MeshComp->GetOwner()) // 캐릭터 제외
		{
			Actor->CustomTimeDilation = 1.0f; // 시간 복원
		}
	}
}
