#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROJECT_NULL_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// 생성자
	AMyCharacter();

protected:
	// 게임 시작 시 호출
	virtual void BeginPlay() override;

public:
	// 매 프레임 호출
	virtual void Tick(float DeltaTime) override;

	// 블루프린트에서 호출 가능한 함수 - 모든 캐릭터 정지
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (DisplayName = "Freeze All Other Characters"))
	void FreezeAllOtherCharacters();

	// 블루프린트에서 호출 가능한 함수 - 모든 캐릭터 다시 활성화
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (DisplayName = "Unfreeze All Other Characters"))
	void UnfreezeAllOtherCharacters();
};
