# SURFKINI — Master Game Architecture & Feature Specification
## Unreal Engine 5.4 | Massive Parallel Agent CS-Surf Shooter

---

## 🎮 Core Vision & Philosophy: "Agents Everywhere"

**SURFKINI** merges **CS/Source-style momentum surf physics** with a **massive parallel AI agent hierarchy**, where hundreds to thousands of AI-driven entities operate simultaneously across gameplay, world systems, tactical coordination, and dynamic difficulty.

```
+-----------------------------------------------------------------------------------+
|                                  SURFKINI ENGINE                                  |
+-----------------------------------------------------------------------------------+
|  PHYSICS LAYER        | Quake/Source PM_ClipVelocity (Clean-room, overbounce 1.001f) |
|                       | Fixed 60Hz physics tick, render-decoupled visual lerp     |
+-----------------------+-----------------------------------------------------------+
|  AI AGENT HIERARCHY   | Micro-Agents:  10,000+ GPU particles/bullets (Niagara)     |
|                       | Meso-Agents:   500+ surf NPCs (UMassEntity + BehaviorTree) |
|                       | Macro-Agents:  10 Squad Leaders (RL ONNX models)          |
|                       | Meta-Agents:   1 World Manager (Procedural difficulty)    |
+-----------------------+-----------------------------------------------------------+
|  NETWORKING LAYER     | Server Authoritative (64Hz) + Client Prediction & Rollback |
|                       | Lag Compensation (Hitbox rewind buffer) + ENet / WebRTC  |
+-----------------------------------------------------------------------------------+
```

---

## 🚀 1. Massive Parallel AI Agent Hierarchy

### Layer Breakdown

| Layer | Entity Count | Performance Target | Implementation | Responsibility |
|-------|--------------|--------------------+----------------+----------------|
| **Micro-Agents** | 10,000+ | < 1 ms CPU | Niagara Compute Shaders + GPU Physics | Bullets, ricochets, debris, particle swarms |
| **Meso-Agents** | 500+ | < 5 ms CPU | `UMassEntity` + `USurfMassProcessor` | Surf-capable enemy NPCs, flocking zombies |
| **Macro-Agents**| 10-20 | < 2 ms CPU | ONNX Runtime + C++ Neural Inference | Squad leaders, flankers, adaptive tactics |
| **Meta-Agents** | 1 | < 0.5 ms CPU | Background Worker Thread | Dynamic difficulty, procedural level events |

---

## 📐 2. Physics & Surf Mathematics

### A. Surface Classification
- Walkable Ground: `HitNormal.Z >= 0.707f` (cos 45°). Applies friction and ground acceleration.
- Surf Ramp: `0.0f < HitNormal.Z < 0.707f`. Bypasses friction, applies clean-room `ClipVelocity`.
- Wall / Ceiling: `HitNormal.Z <= 0.0f`. Clips velocity along normal plane.

### B. Air-Strafe Acceleration Formula
```
V_proj   = dot(Velocity, WishDir)
AddSpeed = max(0, AirSpeedCap - V_proj)
AccelStep = min(AddSpeed, AirAccel * AirSpeedCap * DeltaTime)
Velocity += AccelStep * WishDir
```
When `WishDir` is perpendicular to `Velocity`, `V_proj = 0`, allowing continuous acceleration along a curved path.

---

## ⚔️ 3. Combat, Weapons & Lag Compensation

### A. Weapon Specifications
- **Assault Rifle**: Hitscan, 666 RPM, 35 Base Damage, 70% Armor Ratio.
- **Physics Cannon**: Projectile Micro-Agent, velocity-inherited movement.
- **Armor Absorption**: `DamageToHealth = Damage * ArmorRatio`, `DamageToArmor = Damage * (1 - ArmorRatio)`.

### B. Lag Compensation (Hitbox Rewind)
- Server maintains 1000ms ring buffer of all player capsule locations.
- When client fires at timestamp `T`, server rewinds all enemy hitboxes to time `T`, performs line trace, applies damage, and restores hitboxes.

---

## 🌐 4. Networking & Multiplayer Architecture

- Server Authority: 64Hz locked tick.
- Client Prediction: Client executes movement immediately and saves `FSurfSavedMove` to a 128-tick ring buffer.
- Reconciliation: If server position error exceeds `0.005f` units, client snaps position to server state and replays remaining saved moves.

---

## 📁 5. Directory Scope & Parallel Agent Assignment

- `Source/SURFKINI/Movement/`: SurfMovementComponent, SurfMovementReplicator
- `Source/SURFKINI/Weapons/`: WeaponBase, RifleWeapon, ProjectileWeapon, LagCompensator
- `Source/SURFKINI/AI/`: SurfMassProcessor, SurfEnemyController, SquadLeaderAI
- `Source/SURFKINI/Net/`: NetDriver, Matchmaking, ENetTransport
- `Source/SURFKINI/UI/`: SURFKINIHud, SpeedMeterWidget, ScoreboardWidget
