#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "NiagaraSystem.h"
#include "NiagaraEffectNotify.generated.h"

UCLASS()
class PROJECT_NULL_API UNiagaraEffectNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// 이펙트 템플릿 (Niagara 시스템)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* EffectTemplate;

	// 이펙트 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float EffectRadius = 500.0f;

	// Notify 호출 시 실행되는 함수
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
