#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROJECT_NULL_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Dash function
	void Dash();

	// Dash properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashDistance = 1000.0f; // 기본 거리 설정

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashSpeedMultiplier = 1.0f; // 대시 속도 조절용

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashCooldown = 1.0f;

	// 애니메이션 몽타주 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	class UAnimMontage* DashMontage;

	// Check if dash is available
	bool bCanDash;

	// Function to set dash availability
	void ResetDash();

	// Input binding
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
