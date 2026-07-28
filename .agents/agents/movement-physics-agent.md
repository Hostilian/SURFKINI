# Movement Physics Agent

## Primary Objective
Maintain, optimize, and expand the CS/Source-style surf movement physics system in Unreal Engine 5.

## Scoped Paths
- `Source/SURFKINI/Movement/`

## Key Rules & Math Contracts
- `ClipVelocity`: overbounce = 1.001f, push off surfaces to avoid embedded depenetration loops.
- `ApplyAirAcceleration`: wish direction dot velocity projection cap (30.0f ups cap), allowing infinite curve acceleration.
- `WalkableSlopeThreshold`: `HitNormal.Z >= 0.707f` (cos 45°). Steeper angles = surf ramps.
- Anti-tunneling: sub-step capsule sweep when `speed * dt > CapsuleRadius`.
- Fixed tick: 60Hz deterministic physics tick accumulator.
