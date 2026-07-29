// SURFKINI — Custom Surf Movement Component Implementation
//
// Clean-room Source/Quake physics. No Valve SDK code.
// See SurfMovementComponent.h for detailed math documentation.

#include "Movement/SurfMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"

// ─────────────────────────────────────────────────────────────────────────────
//  Construction & Lifecycle
// ─────────────────────────────────────────────────────────────────────────────

USurfMovementComponent::USurfMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// Physics tick runs at fixed rate — visual interpolation is handled by character
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
}

void USurfMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	Velocity = FVector::ZeroVector;
	MoveState = ESurfMoveState::Airborne;
}

// ─────────────────────────────────────────────────────────────────────────────
//  External Input API
// ─────────────────────────────────────────────────────────────────────────────

void USurfMovementComponent::AddWishDirection(FVector WorldDirection, float ScaleValue)
{
	// Flatten to XY — vertical wish direction is meaningless in surf
	WorldDirection.Z = 0.0f;
	WorldDirection.Normalize();
	AccumulatedWishDir += WorldDirection * ScaleValue;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Fixed-Tick Accumulator
// ─────────────────────────────────────────────────────────────────────────────

void USurfMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent) return;

	// Accumulate time and process fixed ticks
	TickAccumulator += DeltaTime;

	while (TickAccumulator >= FixedTickRate)
	{
		SimulateTick(FixedTickRate);
		TickAccumulator -= FixedTickRate;
	}

	// Flush input — consumed by SimulateTick above
	AccumulatedWishDir = FVector::ZeroVector;
	// Note: bJumpRequested is NOT reset here — it's consumed in ProcessJump()
	// to handle the sub-tick jump window properly
}

// ─────────────────────────────────────────────────────────────────────────────
//  Core Simulation Tick
// ─────────────────────────────────────────────────────────────────────────────

void USurfMovementComponent::SimulateTick(float DeltaTime)
{
	// --- Build wish direction from accumulated input ---
	FVector WishDir = AccumulatedWishDir;
	float WishSpeed = 0.0f;

	if (!WishDir.IsNearlyZero())
	{
		WishDir.Normalize();
		WishSpeed = (MoveState == ESurfMoveState::Grounded)
		            ? MaxGroundSpeed
		            : MaxAirSpeed;
	}

	// --- State-dependent movement ---
	switch (MoveState)
	{
	case ESurfMoveState::Grounded:
		// Apply friction first, then ground acceleration
		Velocity = ApplyFriction(Velocity, DeltaTime);
		Velocity = ApplyGroundAcceleration(Velocity, WishDir, WishSpeed, DeltaTime);
		ProcessJump();
		break;

	case ESurfMoveState::Airborne:
	case ESurfMoveState::Surfing:
		// Air accelerate — enables the strafe trick
		Velocity = ApplyAirAcceleration(Velocity, WishDir, MaxAirSpeed, DeltaTime);
		ApplyGravity(DeltaTime);
		break;

	case ESurfMoveState::Noclip:
		// Debug flight — ignore physics
		{
			FVector NoclipDir = WishDir;
			NoclipDir.Z = 0.0f;
			Velocity = NoclipDir * MaxGroundSpeed * 2.0f;
		}
		break;
	}

	// --- Sweep and resolve collisions ---
	// This updates MoveState based on what surfaces we hit
	PerformSweepAndSlide(DeltaTime);

	// --- Save move for client prediction ---
	CurrentTickID++;
	SavedMoveHead = CurrentTickID % SavedMoveCount;
	FSurfSavedMove& Move = SavedMoves[SavedMoveHead];
	Move.TickID       = CurrentTickID;
	Move.DeltaSeconds = DeltaTime;
	Move.WishDirection = WishDir;
	Move.bJumpPressed  = bJumpRequested;
	Move.Position      = UpdatedComponent->GetComponentLocation();
	Move.Velocity      = Velocity;
	Move.MoveState     = MoveState;

	// Reset jump after saving
	bJumpRequested = false;

	// Track time since grounded (for coyote time, sound triggers, etc.)
	if (MoveState != ESurfMoveState::Grounded)
	{
		TimeSinceLastGrounded += DeltaTime;
	}
	else
	{
		TimeSinceLastGrounded = 0.0f;
	}
}

// ─────────────────────────────────────────────────────────────────────────────
//  ClipVelocity — PM_ClipVelocity clean-room reimplementation
//
//  Removes the component of velocity moving INTO the surface plane.
//  The overbounce coefficient (1.001) applies a tiny push away from the surface
//  to prevent the capsule from being mathematically embedded in geometry.
// ─────────────────────────────────────────────────────────────────────────────

FVector USurfMovementComponent::ClipVelocity(const FVector& VelocityIn,
                                              const FVector& Normal,
                                              float Overbounce) const
{
	// Scalar projection of velocity onto the normal
	const float Backoff = FVector::DotProduct(VelocityIn, Normal);

	// If we're moving AWAY from the surface, do not clip
	if (Backoff >= 0.0f)
	{
		return VelocityIn;
	}

	// Remove the into-surface component (with overbounce push-off)
	FVector VelocityOut = VelocityIn - Normal * (Backoff * Overbounce);

	// Second-pass correction: eliminate floating-point residual into-surface component
	const float Residual = FVector::DotProduct(VelocityOut, Normal);
	if (Residual < 0.0f)
	{
		VelocityOut -= Normal * Residual;
	}

	return VelocityOut;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ApplyAirAcceleration — Source-style air strafe
//
//  The loophole: we cap the PROJECTION of velocity onto wish_direction
//  (V_proj), NOT the absolute speed. So when wish_direction is perpendicular
//  to velocity, V_proj = 0 and the full MaxAirSpeed can be added each tick.
//
//  By keeping wish_dir perpendicular to velocity (A/D key + matching mouse yaw),
//  the player accelerates indefinitely along a curved path → air strafe.
// ─────────────────────────────────────────────────────────────────────────────

FVector USurfMovementComponent::ApplyAirAcceleration(const FVector& InVelocity,
                                                      const FVector& WishDir,
                                                      float WishSpeed,
                                                      float DeltaTime) const
{
	if (WishDir.IsNearlyZero()) return InVelocity;

	// V_proj: current speed along the wish direction
	const float VProj = FVector::DotProduct(InVelocity, WishDir);

	// How much more speed we can add along wish direction before hitting the cap
	const float AddSpeed = WishSpeed - VProj;
	if (AddSpeed <= 0.0f) return InVelocity;

	// Acceleration step this tick (capped at AddSpeed)
	const float AccelStep = FMath::Min(AddSpeed, AirAcceleration * WishSpeed * DeltaTime);

	return InVelocity + WishDir * AccelStep;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ApplyGroundAcceleration — Quake-style ground acceleration
// ─────────────────────────────────────────────────────────────────────────────

FVector USurfMovementComponent::ApplyGroundAcceleration(const FVector& InVelocity,
                                                         const FVector& WishDir,
                                                         float WishSpeed,
                                                         float DeltaTime) const
{
	if (WishDir.IsNearlyZero()) return InVelocity;

	const float VProj     = FVector::DotProduct(InVelocity, WishDir);
	const float AddSpeed  = WishSpeed - VProj;
	if (AddSpeed <= 0.0f) return InVelocity;

	const float AccelStep = FMath::Min(AddSpeed, GroundAcceleration * WishSpeed * DeltaTime);

	return InVelocity + WishDir * AccelStep;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ApplyFriction — Quake-style ground friction
//
//  StopSpeed prevents the "creep forever" bug where tiny velocity
//  never fully decays due to multiplicative friction.
// ─────────────────────────────────────────────────────────────────────────────

FVector USurfMovementComponent::ApplyFriction(const FVector& InVelocity, float DeltaTime) const
{
	// Only apply to horizontal plane (Z handled by gravity)
	FVector HorizVelocity = FVector(InVelocity.X, InVelocity.Y, 0.0f);
	const float Speed = HorizVelocity.Size();

	if (Speed < SMALL_NUMBER) return InVelocity;

	// Friction drop: deceleration this tick
	const float Control  = FMath::Max(Speed, StopSpeed);
	const float Drop     = Control * GroundFriction * DeltaTime;
	const float NewSpeed = FMath::Max(0.0f, Speed - Drop) / Speed;

	return FVector(InVelocity.X * NewSpeed, InVelocity.Y * NewSpeed, InVelocity.Z);
}

float USurfMovementComponent::CalculateKineticWallDamage(float ImpactSpeed) const
{
	if (ImpactSpeed <= KineticDamageThreshold)
	{
		return 0.0f;
	}
	const float ExcessSpeed = ImpactSpeed - KineticDamageThreshold;
	return KineticDamageCoefficient * ExcessSpeed * ExcessSpeed;
}


// ─────────────────────────────────────────────────────────────────────────────
//  ApplyGravity
// ─────────────────────────────────────────────────────────────────────────────

FVector USurfMovementComponent::SmoothFacetNormal(const FVector& CurrentNormal)
{
	if (LastGroundNormal.IsNearlyZero()) return CurrentNormal;

	const float Dot = FVector::DotProduct(LastGroundNormal, CurrentNormal);
	const float AngleDegrees = FMath::RadiansToDegrees(FMath::Acos(FMath::Clamp(Dot, -1.0f, 1.0f)));

	// If sudden seam angle disparity on non-walkable surf ramp, interpolate normal to prevent snagging
	if (AngleDegrees > FacetNormalSmoothingThresholdDegrees && CurrentNormal.Z > 0.0f && CurrentNormal.Z < WalkableSlopeThreshold)
	{
		FVector Smoothed = (LastGroundNormal + CurrentNormal).GetSafeNormal();
		return Smoothed;
	}

	return CurrentNormal;
}

void USurfMovementComponent::RequestJump()
{
	bJumpRequested = true;
	// Activate subtick jump buffer window
	TimeSinceLastGrounded = 0.0f;
}

void USurfMovementComponent::ProcessJump()
{
	if (!bJumpRequested) return;

	// Grounded OR within Coyote Window (100ms grace window after leaving ramp edge)
	const bool bCanJump = (MoveState == ESurfMoveState::Grounded) || (TimeSinceLastGrounded <= CoyoteWindowDuration);

	if (!bCanJump) return;

	// Apply jump impulse
	Velocity.Z = JumpForce;
	MoveState = ESurfMoveState::Airborne;
	bJumpRequested = false;
}

void USurfMovementComponent::ApplyGravity(float DeltaTime)
{
	Velocity.Z -= Gravity * DeltaTime;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ClassifyGroundContact
//
//  A surface is walkable if its up-facing normal Z >= cos(45°) ≈ 0.707.
//  Steeper than 45° → surf ramp (no friction, clip velocity applied).
// ─────────────────────────────────────────────────────────────────────────────

void USurfMovementComponent::ClassifyGroundContact(const FVector& HitNormal)
{
	if (HitNormal.Z >= WalkableSlopeThreshold)
	{
		MoveState = ESurfMoveState::Grounded;
		LastGroundNormal = HitNormal;
	}
	else if (HitNormal.Z > 0.0f)
	{
		// Steep ramp — enter surf state (no friction, keep momentum)
		MoveState = ESurfMoveState::Surfing;
		LastGroundNormal = HitNormal;
	}
	// HitNormal.Z <= 0 = wall or ceiling — do not change ground state
}

// ─────────────────────────────────────────────────────────────────────────────
//  PerformSweepAndSlide — Custom kinematic loop
//
//  Replaces UCharacterMovementComponent's move_and_slide.
//  Uses move_and_collide equivalent (SweepComponent) with up to MaxBumps
//  collision iterations per tick.
//
//  Anti-tunnel: when speed * Δt > CapsuleRadius, splits into sub-steps.
//  This prevents fast-moving players from clipping through thin ramps.
// ─────────────────────────────────────────────────────────────────────────────

void USurfMovementComponent::PerformSweepAndSlide(float DeltaTime)
{
	if (!UpdatedComponent || !PawnOwner) return;

	UWorld* World = GetWorld();
	if (!World) return;

	// ── Anti-tunnel sub-stepping ──
	const float StepDistance = Velocity.Size() * DeltaTime;
	const int32 SubSteps     = FMath::Max(1, FMath::CeilToInt(StepDistance / CapsuleRadius));
	const float SubDelta     = DeltaTime / (float)SubSteps;

	// Assume airborne until a contact normal proves otherwise
	bool bTouchedGround = false;
	MoveState = ESurfMoveState::Airborne;

	for (int32 Sub = 0; Sub < SubSteps; ++Sub)
	{
		FVector MoveDelta = Velocity * SubDelta;
		FVector RemainingDelta = MoveDelta;

		// ── Iterative bump resolution (PM_SlideMove equivalent) ──
		for (int32 Bump = 0; Bump < MaxBumps && !RemainingDelta.IsNearlyZero(); ++Bump)
		{
			FHitResult Hit;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(PawnOwner);

			const FVector StartPos = UpdatedComponent->GetComponentLocation();
			const FVector EndPos   = StartPos + RemainingDelta;

			// Capsule sweep
			const bool bHit = World->SweepSingleByChannel(
				Hit,
				StartPos,
				EndPos,
				UpdatedComponent->GetComponentQuat(),
				ECC_Pawn,
				FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
				QueryParams
			);

			if (!bHit)
			{
				// No collision — move the full remaining delta
				UpdatedComponent->MoveComponent(RemainingDelta, UpdatedComponent->GetComponentQuat(), false);
				RemainingDelta = FVector::ZeroVector;
				break;
			}

			// Move to the point just before impact (SafeLocation)
			const FVector SafeMove = RemainingDelta * Hit.Time;
			if (!SafeMove.IsNearlyZero())
			{
				UpdatedComponent->MoveComponent(SafeMove, UpdatedComponent->GetComponentQuat(), false);
			}

			// Classify contact surface (updates MoveState)
			ClassifyGroundContact(Hit.ImpactNormal);
			if (MoveState == ESurfMoveState::Grounded || MoveState == ESurfMoveState::Surfing)
			{
				bTouchedGround = true;
			}

			// Clip velocity along the surface — removes into-surface component
			Velocity = ClipVelocity(Velocity, Hit.ImpactNormal, ClipOverbounce);

			// Remaining delta after impact = clip it too (continue sliding)
			RemainingDelta = ClipVelocity(
				RemainingDelta * (1.0f - Hit.Time),
				Hit.ImpactNormal,
				ClipOverbounce
			);
		}
	}

	// If we never touched a surface, we're airborne
	if (!bTouchedGround)
	{
		MoveState = ESurfMoveState::Airborne;
	}
}
