#include "InputDisable.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"

void UInputDisable::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character)
	{
		// Disable input for the character
		Character->DisableInput(Cast<APlayerController>(Character->GetController()));
	}
}

void UInputDisable::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character)
	{
		// Re-enable input for the character
		Character->EnableInput(Cast<APlayerController>(Character->GetController()));
	}
}
