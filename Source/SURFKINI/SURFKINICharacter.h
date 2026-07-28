// SURFKINI — Player Character Header
//
// Owns the SurfMovementComponent.
// Handles input, camera, and replicated state.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Movement/SurfMovementComponent.h"
#include "SURFKINICharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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

	// ── Accessors ─────────────────────────────────────────────────
	UFUNCTION(BlueprintPure, Category = "Character")
	USurfMovementComponent* GetSurfMovement() const { return SurfMovement; }

protected:
	// ── Components ────────────────────────────────────────────────

	/** Custom surf physics component — replaces CharacterMovementComponent logic */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
	          meta = (AllowPrivateAccess = "true"))
	USurfMovementComponent* SurfMovement;

	/** First-person camera — mounted directly to capsule (no spring arm) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera",
	          meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCamera;

	// ── Visual Interpolation ──────────────────────────────────────
	// The visual mesh lags slightly behind physics for smooth high-Hz rendering.
	// Physics runs at 60Hz; rendering can be 144Hz+ with smooth interpolation.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rendering")
	FVector VisualPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	float VisualLerpSpeed = 30.0f;

	// ── Input Handlers ────────────────────────────────────────────
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void OnJumpPressed();
	void OnJumpReleased();

	// ── Camera Clamp ──────────────────────────────────────────────
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxPitchDegrees = 89.0f;

	float CurrentPitch = 0.0f;
};
