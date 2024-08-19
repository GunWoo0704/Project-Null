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

	// 맵에 있는 모든 캐릭터들을 가져오기
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(Initiator->GetWorld(), ACharacter::StaticClass(), FoundCharacters);

	// 각 캐릭터들에 대해 반복
	for (AActor* Actor : FoundCharacters)
	{
		ACharacter* Character = Cast<ACharacter>(Actor);
		if (Character && Character != Initiator)  // 플레이어 캐릭터가 아닌 경우
		{
			FVector CharacterLocation = Character->GetActorLocation();

			// 캐릭터가 설정된 범위 안에 있는지 확인
			float Distance = FVector::Dist(PlayerLocation, CharacterLocation);
			if (Distance <= PushRadius)
			{
				// 플레이어와 캐릭터 사이의 방향 벡터를 구한다.
				FVector Direction = CharacterLocation - PlayerLocation;
				Direction.Z = 0;  // XY 평면에서만 밀어내기 위해 Z 값을 0으로 설정
				Direction.Normalize();  // 방향 벡터 정규화

				// 밀어내는 힘 설정 (에디터에서 설정한 값 사용)
				FVector PushForce = Direction * PushStrength;

				// 캐릭터를 밀어내기
				UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
				if (MovementComponent)
				{
					MovementComponent->AddImpulse(PushForce, true);
				}
			}
		}
	}
}
