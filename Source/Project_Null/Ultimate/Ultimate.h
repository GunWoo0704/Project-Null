#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomCharacter.generated.h"

UCLASS()
class PROJECT_NULL_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACustomCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Function to handle camera rotation
	void RotateCameraAroundCharacter();

private:
	float CameraRotationSpeed = 50.0f;  // Speed of camera rotation around character
};
