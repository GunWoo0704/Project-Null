#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// �⺻ ��� ���� ����
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
	// ĳ���Ͱ� ���߿� ���� �ʰ� ��� ������ ���� ����
	if (bCanDash && GetCharacterMovement()->IsFalling() == false)
	{
		// ĳ���Ͱ� �ٶ󺸴� ������ ������
		FVector DashDirection = GetActorForwardVector();
		DashDirection.Z = 0; // Z �� ����

		// �ӵ� ������ ���� ó��
		FVector LaunchVelocity = DashDirection.GetSafeNormal() * DashDistance * DashSpeedMultiplier;
		LaunchVelocity.Z = 0; // Z ���� 0���� ����

		// ĳ���͸� �ٶ󺸴� �������� ���
		LaunchCharacter(LaunchVelocity, true, true);

		// ��� �ִϸ��̼� ��Ÿ�� ���
		if (DashMontage && GetMesh() && GetMesh()->GetAnimInstance())
		{
			GetMesh()->GetAnimInstance()->Montage_Play(DashMontage);
		}

		// ��� �Ұ����ϰ� ���� ��, ��Ÿ�� �� �ٽ� �����ϵ��� ��
		bCanDash = false;

		// FTimerHandle ����
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

	// ��Ŭ�� (Right Mouse Button) �Է� ���ε�
	PlayerInputComponent->BindAction("RightMouse", IE_Pressed, this, &AMyCharacter::Dash);
}
