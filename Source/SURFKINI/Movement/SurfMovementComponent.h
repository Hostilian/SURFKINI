// SURFKINI — Custom Surf Movement Component
//
// Implements CS/Source-style surf physics:
//   - Quake/Source ClipVelocity (PM_ClipVelocity)
//   - Air acceleration with perpendicular wish_direction strafe trick
//   - Ramp sliding: surface normal Z >= cos(45°) = 0.707 threshold
//   - Deterministic 60Hz fixed tick
//
// LEGAL NOTE: This is a clean-room reimplementation of the
// mathematical physics model. No Valve Source SDK code was used.
// Reference: EricXu1728/Godot4SourceEngineMovement (MIT license) — math only.

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

	// ── State Accessors ─────────────────────────────────────────

	UFUNCTION(BlueprintPure, Category = "SurfMovement")
	ESurfMoveState GetMoveState() const { return MoveState; }

	UFUNCTION(BlueprintPure, Category = "SurfMovement")
	float GetHorizontalSpeed() const { return Velocity.Size2D(); }

	UFUNCTION(BlueprintPure, Category = "SurfMovement")
	bool IsGrounded() const { return MoveState == ESurfMoveState::Grounded; }

	UFUNCTION(BlueprintPure, Category = "SurfMovement")
	bool IsSurfing() const  { return MoveState == ESurfMoveState::Surfing; }

	// ── Network: Client Prediction Buffer ───────────────────────
	/** Returns the latest saved move for server reconciliation */
	const FSurfSavedMove& GetLatestSavedMove() const { return SavedMoves[SavedMoveHead]; }

	// ── Tuning Parameters (editable in editor) ────────────────

	// --- Ground Movement ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ground")
	float MaxGroundSpeed = 320.0f;         // UUs/s — ~285 ups Source equivalent

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ground")
	float GroundAcceleration = 10.0f;      // Ground accel coefficient

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ground")
	float GroundFriction = 4.0f;           // Quake-style friction coefficient

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ground")
	float StopSpeed = 100.0f;              // Speed below which friction stops player

	// --- Air Movement ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Air")
	float MaxAirSpeed = 30.0f;             // Source competitive air speed cap (30 ups)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Air")
	float AirAcceleration = 10.0f;         // Air accel coefficient (sv_airaccelerate)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Air")
	float Gravity = 800.0f;               // UUs/s² downward acceleration

	// --- Jumping ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Jump")
	float JumpForce = 301.993377f;         // Source jump height: sqrt(2 * 800 * 57) ≈ 302

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Jump")
	float JumpSubtickWindow = 0.008f;      // Sub-tick jump window (prevents losing jump on frame boundary)

	// --- Surf Ramp Detection ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Surf")
	float WalkableSlopeThreshold = 0.707f; // cos(45°) — slopes steeper than this are surf ramps

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Surf")
	float ClipOverbounce = 1.001f;         // Prevents embedding in surface (epsilon push-off)

	// --- Collision ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Collision")
	float CapsuleRadius = 16.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Collision")
	float CapsuleHalfHeight = 36.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Collision")
	int32 MaxBumps = 3;                    	// --- Ground & Ramp Grace Timers ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Jump")
	float CoyoteWindowDuration = 0.100f;   // 100ms coyote time window after leaving ramp edge

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Jump")
	float SubtickJumpBufferDuration = 0.008f; // 8ms subtick jump buffer window

	// --- Edge Smoothing ---
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfMovement|Ramp")
	float FacetNormalSmoothingThresholdDegrees = 15.0f; // Max angle delta before smoothing ramp seam normal

protected:
	/** Smooths anomalous seam contact normals to prevent ramp edge snagging */
	FVector SmoothFacetNormal(const FVector& CurrentNormal);

	// ── Core Physics Methods ─────────────────────────────────────────

	/**
	 * ClipVelocity — PM_ClipVelocity clean-room reimplementation.
	 *
	 * Projects velocity onto the collision plane, removing the component
	 * moving INTO the surface. Uses overbounce to prevent embedding.
	 *
	 * Math:
	 *   backoff     = dot(VelocityIn, Normal) * Overbounce
	 *   VelocityOut = VelocityIn - Normal * backoff
	 */
	FVector ClipVelocity(const FVector& VelocityIn, const FVector& Normal, float Overbounce) const;

	/**
	 * ApplyAirAcceleration — Source-style air strafe acceleration.
	 *
	 * Key property: caps the PROJECTION of velocity onto wish_direction
	 * rather than the absolute speed. This is the mathematical basis for
	 * the air-strafe speed gain trick.
	 *
	 * Math per tick (Δt):
	 *   V_proj   = dot(Velocity, WishDir)               // current speed along wish dir
	 *   A_add    = max(0, AirSpeedCap - V_proj)         // how much we can still add
	 *   A_step   = min(A_add, AirAccel * WishSpeed * Δt)
	 *   Velocity += A_step * WishDir
	 */
	FVector ApplyAirAcceleration(const FVector& InVelocity, const FVector& WishDir,
	                             float WishSpeed, float DeltaTime) const;

	/**
	 * ApplyGroundAcceleration — Quake-style ground acceleration.
	 * Same projection trick as air accel but with MaxGroundSpeed cap.
	 */
	FVector ApplyGroundAcceleration(const FVector& InVelocity, const FVector& WishDir,
	                                float WishSpeed, float DeltaTime) const;

	/**
	 * ApplyFriction — Quake-style ground friction.
	 *
	 * Math:
	 *   speed    = |Velocity|
	 *   drop     = max(speed, StopSpeed) * Friction * Δt
	 *   newspeed = max(0, speed - drop) / speed
	 *   Velocity *= newspeed
	 */
	FVector ApplyFriction(const FVector& InVelocity, float DeltaTime) const;

	/**
	 * PerformSweepAndSlide — Custom kinematic loop (replaces move_and_slide).
	 *
	 * Sweeps the capsule along the velocity vector, resolves collisions via
	 * ClipVelocity, and determines whether we are grounded or surfing based
	 * on the contact normal's Z component vs WalkableSlopeThreshold.
	 *
	 * Anti-tunnel: when |Velocity| * Δt > CapsuleRadius, splits into sub-steps.
	 */
	void PerformSweepAndSlide(float DeltaTime);

	/** Classify the current contact normal to update MoveState */
	void ClassifyGroundContact(const FVector& HitNormal);

	/** Apply gravity downward acceleration */
	void ApplyGravity(float DeltaTime);

	/** Perform jump if bJumpRequested and grounded */
	void ProcessJump();

	/** Tick the physics accumulator — called once per physics tick */
	void SimulateTick(float DeltaTime);

	// ── State ───────────────────────────────────────────────────────

	UPROPERTY(VisibleInstanceOnly, Category = "SurfMovement|Debug")
	ESurfMoveState MoveState = ESurfMoveState::Airborne;

	UPROPERTY(VisibleInstanceOnly, Category = "SurfMovement|Debug")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(VisibleInstanceOnly, Category = "SurfMovement|Debug")
	FVector LastGroundNormal = FVector::UpVector;

	UPROPERTY(VisibleInstanceOnly, Category = "SurfMovement|Debug")
	float TimeSinceLastGrounded = 0.0f;

	// Input accumulator (flushed each tick)
	FVector   AccumulatedWishDir = FVector::ZeroVector;
	bool      bJumpRequested     = false;

	// Sub-tick accumulator for fixed 60Hz
	float     TickAccumulator    = 0.0f;
	const float FixedTickRate    = 1.0f / 60.0f;

	// Client prediction ring buffer (128 ticks)
	static constexpr int32 SavedMoveCount = 128;
	FSurfSavedMove SavedMoves[SavedMoveCount];
	int32          SavedMoveHead = 0;
	int32          CurrentTickID = 0;
};
