# SURFKINI — Unreal Engine Prototype Audit & Migration Report

> **Archive Baseline Hash**: `e20dd43`  
> **Engine Association**: `Unreal Engine 5.8` (`SURFKINI.uproject`)  
> **Archive Tag**: `unreal-prototype-2026-07`

---

## 1. Subsystem Classification Matrix

| File Path | Original Purpose | Reusability Category | Migration Pathway |
| :--- | :--- | :--- | :--- |
| `Source/SURFKINI/Movement/SurfMovementComponent.h/.cpp` | Custom Movement Component | **Reusable Concept** | Port `ClipVelocity` & Friction math to Godot GDScript & UE C++ solver |
| `Source/SURFKINI/Weapons/AWeaponBase.h/.cpp` | Weapon Actor Base | **Reusable Architecture** | Port hitscan raycast & recoil pattern math to `weapon_base.gd` |
| `Source/SURFKINI/Net/SurfMovementReplicator.h/.cpp` | Client Prediction Buffer | **Reusable Data Schema** | Port circular snapshot buffer schema to `net_snapshot_buffer.gd` |
| `Source/SURFKINI/UI/ASURF_HUD.h/.cpp` | HUD Renderer | **Concept Only** | Re-implement in Godot Control Nodes (`hud.gd`, `speedometer.gd`) |
| `Source/SURFKINI/World/ASurfTestMapBuilder.h/.cpp` | Procedural Level Builder | **Reusable Logic** | Port ramp mesh generation to `ramp_generator.gd` |

---

## 2. Gameplay Constants & Physics Directives

```cpp
// Source: Valve Source Engine Surf Mechanics (Clean-Room Port Constants)
constexpr float SURF_DEFAULT_GRAVITY = 800.0f;
constexpr float SURF_DEFAULT_AIR_ACCELERATION = 150.0f;
constexpr float SURF_DEFAULT_MAX_AIR_SPEED = 30.0f;
constexpr float SURF_DEFAULT_RAMP_FRICTION = 0.0f;
constexpr float SURF_MAX_VELOCITY_CAP = 3500.0f;
```

---

## 3. Migration Roadmap Rules

1. **Unreal Prototype Freeze**: The Unreal Engine C++ prototype archive is preserved in read-only audit mode under tag `unreal-prototype-2026-07`.
2. **Dual-Engine Parity**: All new core movement mathematics must maintain identical physics outputs between Godot GDScript and Unreal C++.
