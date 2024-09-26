#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 기본 대시 가능 상태
	bCanDash = true;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCharacter::Dash()
{
	// 캐릭터가 공중에 있지 않고 대시 가능할 때만 실행
	if (bCanDash && GetCharacterMovement()->IsFalling() == false)
	{
		// 캐릭터가 바라보는 방향을 가져옴
		FVector DashDirection = GetActorForwardVector();
		DashDirection.Z = 0; // Z 축 고정

		// 속도 조절을 위한 처리
		FVector LaunchVelocity = DashDirection.GetSafeNormal() * DashDistance * DashSpeedMultiplier;
		LaunchVelocity.Z = 0; // Z 축을 0으로 고정

		// 캐릭터를 바라보는 방향으로 대시
		LaunchCharacter(LaunchVelocity, true, true);

		// 대시 애니메이션 몽타주 재생
		if (DashMontage && GetMesh() && GetMesh()->GetAnimInstance())
		{
			GetMesh()->GetAnimInstance()->Montage_Play(DashMontage);
		}

		// 대시 불가능하게 설정 후, 쿨타임 후 다시 가능하도록 함
		bCanDash = false;

		// FTimerHandle 선언
		FTimerHandle DashTimerHandle;
		GetWorldTimerManager().SetTimer(
			DashTimerHandle,
			this,
			&AMyCharacter::ResetDash,
			DashCooldown,
			false
		);
	}
}

void AMyCharacter::ResetDash()
{
	bCanDash = true;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 우클릭 (Right Mouse Button) 입력 바인딩
	PlayerInputComponent->BindAction("RightMouse", IE_Pressed, this, &AMyCharacter::Dash);
}
