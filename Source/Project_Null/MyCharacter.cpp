#include "MyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h" // TActorIterator ����� ���� �ʿ�
#include "Animation/AnimInstance.h" // UAnimInstance�� ���� �ʿ�

AMyCharacter::AMyCharacter()
{
	// Tick �Լ� Ȱ��ȭ
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �ʿ� �� Ư�� ���ǿ��� ȣ�� ����
	// FreezeAllOtherCharacters();
	// UnfreezeAllOtherCharacters();
}

void AMyCharacter::FreezeAllOtherCharacters()
{
	// ���� �÷��̾� ĳ���� ��������
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!PlayerCharacter)
		return;

	// ���忡 �����ϴ� ��� ACharacter ��ȸ
	for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
	{
		ACharacter* Character = *It;

		// �÷��̾� ĳ���ʹ� ����
		if (Character == PlayerCharacter)
			continue;

		// �ٸ� ĳ������ Movement Component ��Ȱ��ȭ
		UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
		if (MovementComponent)
		{
			MovementComponent->Deactivate();
		}

		// �ִϸ��̼� ��Ÿ�� ����
		UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
		if (AnimInstance && AnimInstance->Montage_IsPlaying(nullptr))
		{
			AnimInstance->Montage_Stop(0.2f); // 0.2���� ���� �ƿ� �ð�
		}
	}
}

void AMyCharacter::UnfreezeAllOtherCharacters()
{
	// ���� �÷��̾� ĳ���� ��������
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!PlayerCharacter)
		return;

	// ���忡 �����ϴ� ��� ACharacter ��ȸ
	for (TActorIterator<ACharacter> It(GetWorld()); It; ++It)
	{
		ACharacter* Character = *It;

		// �÷��̾� ĳ���ʹ� ����
		if (Character == PlayerCharacter)
			continue;

		// �ٸ� ĳ������ Movement Component �ٽ� Ȱ��ȭ
		UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
		if (MovementComponent)
		{
			MovementComponent->Activate();
		}
	}
}
