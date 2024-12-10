#include "MyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h" // TActorIterator 사용을 위해 필요
#include "Animation/AnimInstance.h" // UAnimInstance를 위해 필요

AMyCharacter::AMyCharacter()
{
	// Tick 함수 활성화
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 필요 시 특정 조건에서 호출 가능
	// FreezeAllOtherCharacters();
	// UnfreezeAllOtherCharacters();
}

void AMyCharacter::FreezeAllOtherCharacters()
{
	// 현재 플레이어 캐릭터 가져오기
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!PlayerCharacter)
		return;

	// 월드에 존재하는 모든 ACharacter 순회
	for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
	{
		ACharacter* Character = *It;

		// 플레이어 캐릭터는 제외
		if (Character == PlayerCharacter)
			continue;

		// 다른 캐릭터의 Movement Component 비활성화
		UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
		if (MovementComponent)
		{
			MovementComponent->Deactivate();
		}

		// 애니메이션 몽타주 멈춤
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
		if (AnimInstance && AnimInstance->Montage_IsPlaying(nullptr))
		{
			AnimInstance->Montage_Stop(0.2f); // 0.2초의 블렌드 아웃 시간
		}
	}
}

void AMyCharacter::UnfreezeAllOtherCharacters()
{
	// 현재 플레이어 캐릭터 가져오기
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!PlayerCharacter)
		return;

	// 월드에 존재하는 모든 ACharacter 순회
	for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
	{
		ACharacter* Character = *It;

		// 플레이어 캐릭터는 제외
		if (Character == PlayerCharacter)
			continue;

		// 다른 캐릭터의 Movement Component 다시 활성화
		UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
		if (MovementComponent)
		{
			MovementComponent->Activate();
		}
	}
}
