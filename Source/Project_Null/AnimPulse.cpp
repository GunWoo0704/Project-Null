#include "AnimPulse.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPushAwayNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ACharacter* Initiator = Cast<ACharacter>(MeshComp->GetOwner());
		if (Initiator)
		{
			PushAwayCharacters(Initiator);
		}
	}
}

void UPushAwayNotify::PushAwayCharacters(ACharacter* Initiator)
{
	FVector PlayerLocation = Initiator->GetActorLocation();

	// �ʿ� �ִ� ��� ĳ���͵��� ��������
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(Initiator->GetWorld(), ACharacter::StaticClass(), FoundCharacters);

	// �� ĳ���͵鿡 ���� �ݺ�
	for (AActor* Actor : FoundCharacters)
	{
		ACharacter* Character = Cast<ACharacter>(Actor);
		if (Character && Character != Initiator)  // �÷��̾� ĳ���Ͱ� �ƴ� ���
		{
			FVector CharacterLocation = Character->GetActorLocation();

			// ĳ���Ͱ� ������ ���� �ȿ� �ִ��� Ȯ��
			float Distance = FVector::Dist(PlayerLocation, CharacterLocation);
			if (Distance <= PushRadius)
			{
				// �÷��̾�� ĳ���� ������ ���� ���͸� ���Ѵ�.
				FVector Direction = CharacterLocation - PlayerLocation;
				Direction.Z = 0;  // XY ��鿡���� �о�� ���� Z ���� 0���� ����
				Direction.Normalize();  // ���� ���� ����ȭ

				// �о�� �� ���� (�����Ϳ��� ������ �� ���)
				FVector PushForce = Direction * PushStrength;

				// ĳ���͸� �о��
				UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
				if (MovementComponent)
				{
					MovementComponent->AddImpulse(PushForce, true);
				}
			}
		}
	}
}
