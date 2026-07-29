// SURFKINI — Custom Surf Movement Component
//
// Implements CS/Source-style surf physics:
//   - Quake/Source ClipVelocity (PM_ClipVelocity)
//   - Air acceleration with perpendicular wish_direction strafe trick
//   - Ramp sliding: surface normal Z >= cos(45°) = 0.707 threshold
//   - Kinetic wall-collision damage calculation: Damage = k * (v_impact - v_threshold)^2
//   - Deterministic 60Hz fixed tick

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SurfMovementComponent.generated.h"

// ─────────────────────────────────────────────
//  Enums
// ─────────────────────────────────────────────

UENUM(BlueprintType)
enum class ESurfMoveState : uint8
{
	Grounded   UMETA(DisplayName = "Grounded"),
	Airborne   UMETA(DisplayName = "Airborne"),
	Surfing    UMETA(DisplayName = "Surfing"),  // Sliding on steep ramp (Z normal < 0.707)
	Noclip     UMETA(DisplayName = "Noclip"),   // Debug mode
};

// ─────────────────────────────────────────────
//  Saved Move (for client-side prediction replay)
// ─────────────────────────────────────────────

USTRUCT()
struct FSurfSavedMove
{
	GENERATED_BODY()

	// Input this tick
	FVector WishDirection = FVector::ZeroVector;
	bool    bJumpPressed  = false;

	// State at end of tick (authoritative result)
	FVector   Position  = FVector::ZeroVector;
	FVector   Velocity  = FVector::ZeroVector;
	ESurfMoveState MoveState = ESurfMoveState::Airborne;

	// Tick identifier
	int32   TickID       = 0;
	float   DeltaSeconds = 0.0f;
};

// ─────────────────────────────────────────────
//  Main Component
// ─────────────────────────────────────────────

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURFKINI_API USurfMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	USurfMovementComponent();

	// ── UActorComponent overrides ───────────────
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// ── External Input ───────────────────────────────────────────

	/** Called by character to add wish direction (from WASD input) */
	UFUNCTION(BlueprintCallable, Category = "SurfMovement")
	void AddWishDirection(FVector WorldDirection, float ScaleValue = 1.0f);

	/** Called by character when Jump is pressed */
	UFUNCTION(BlueprintCallable, Category = "SurfMovement")
	void RequestJump();

	// ── Kinetic Wall Damage ─────────────────────────────────────
	/** Calculates kinetic impact damage: Damage = k * max(0, v_impact - v_threshold)^2 */
	UFUNCTION(BlueprintPure, Category = "SurfMovement|Damage")
	float CalculateKineticWallDamage(float ImpactSpeed) const;

	// ── State Accessors ─────────────────────────────────────────

	UFUNCTION(BlueprintPure, Category = "SurfMovement")
	ESurfMoveState GetMoveState() const { return MoveState; }

	UFUNCTION(BlueprintPure, Category = "SurfMovement")
	FVector GetVelocity() const { return Velocity; }

	UFUNCTION(BlueprintPure, Category = "SurfMovement")
	float GetHorizontalSpeed() const { return Velocity.Size2D(); }

	UFUNCTION(BlueprintPure, Category = "SurfMovement")
	bool IsGrounded() const { return MoveState == ESurfMoveState::Grounded; }

	UFUNCTION(BlueprintPure, Category = "SurfMovement")
	bool IsSurfing() const  { return MoveState == ESurfMoveState::Surfing; }

	// ── Network: Client Prediction Buffer ───────────────────────
	const FSurfSavedMove& GetLatestSavedMove() const { return SavedMoves[SavedMoveHead]; }

	// ── Tuning Parameters (editable in editor) ────────────────

	// --- Ground Movement ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ground")
	float MaxGroundSpeed = 320.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ground")
	float GroundAcceleration = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ground")
	float GroundFriction = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ground")
	float StopSpeed = 100.0f;

	// --- Air Movement ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Air")
	float MaxAirSpeed = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Air")
	float AirAcceleration = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Air")
	float Gravity = 800.0f;

	// --- Kinetic Damage Math ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Kinetic")
	float KineticDamageThreshold = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Kinetic")
	float KineticDamageCoefficient = 0.0001f;

	// --- Jumping ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Jump")
	float JumpForce = 301.993377f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Jump")
	float JumpSubtickWindow = 0.008f;

	// --- Surf Ramp Detection ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Surf")
	float WalkableSlopeThreshold = 0.707f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Surf")
	float ClipOverbounce = 1.001f;

	// --- Collision ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Collision")
	float CapsuleRadius = 16.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Collision")
	float CapsuleHalfHeight = 36.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Collision")
	int32 MaxBumps = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Jump")
	float CoyoteWindowDuration = 0.100f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Jump")
	float SubtickJumpBufferDuration = 0.008f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ramp")
	float FacetNormalSmoothingThresholdDegrees = 15.0f;

protected:
	FVector SmoothFacetNormal(const FVector& CurrentNormal);
	FVector ClipVelocity(const FVector& VelocityIn, const FVector& Normal, float Overbounce) const;
	FVector ApplyAirAcceleration(const FVector& InVelocity, const FVector& WishDir,
	                             float WishSpeed, float DeltaTime) const;
	FVector ApplyGroundAcceleration(const FVector& InVelocity, const FVector& WishDir,
	                                float WishSpeed, float DeltaTime) const;
	FVector ApplyFriction(const FVector& InVelocity, float DeltaTime) const;
	void PerformSweepAndSlide(float DeltaTime);
	void ClassifyGroundContact(const FVector& HitNormal);
	void ApplyGravity(float DeltaTime);
	void ProcessJump();
	void SimulateTick(float DeltaTime);

	// ── State ───────────────────────────────────────────────────────

	UPROPERTY(VisibleInstanceOnly, Category = "SurfMovement|Debug")
	ESurfMoveState MoveState = ESurfMoveState::Airborne;

	UPROPERTY(VisibleInstanceOnly, Category = "SurfMovement|Debug")
	FVector LastGroundNormal = FVector::UpVector;

	UPROPERTY(VisibleInstanceOnly, Category = "SurfMovement|Debug")
	float TimeSinceLastGrounded = 0.0f;

	FVector   AccumulatedWishDir = FVector::ZeroVector;
	bool      bJumpRequested     = false;

	float     TickAccumulator    = 0.0f;
	const float FixedTickRate    = 1.0f / 60.0f;

	static constexpr int32 SavedMoveCount = 128;
	FSurfSavedMove SavedMoves[SavedMoveCount];
	int32          SavedMoveHead = 0;
	int32          CurrentTickID = 0;
};
