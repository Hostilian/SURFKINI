// SURFKINI — Player Character Header
//
// Owns the SurfMovementComponent.
// Handles input, 1st/3rd person camera toggling, and Gears wall-impact damage.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Movement/SurfMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SURFKINICharacter.generated.h"

UCLASS()
class SURFKINI_API ASURFKINICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASURFKINICharacter();

	// ── UE Lifecycle ─────────────────────────────────────────────
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// ── Accessors & Camera ─────────────────────────────────────────
	UFUNCTION(BlueprintPure, Category = "Character")
	USurfMovementComponent* GetSurfMovement() const { return SurfMovement; }

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ToggleCameraView();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ApplyWallImpactDamage(float ImpactSpeed);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	USurfMovementComponent* SurfMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* ThirdPersonSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* ThirdPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	bool bIsThirdPerson = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float PlayerHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float PlayerArmor = 100.0f;

	// ── Input Handlers ────────────────────────────────────────────
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void OnJumpPressed();
	void OnJumpReleased();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxPitchDegrees = 89.0f;

	float CurrentPitch = 0.0f;
};
