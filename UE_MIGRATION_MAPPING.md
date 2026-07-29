# SURFKINI — Unreal C++ to Godot GDScript Migration Mapping Register

> **Status**: APPROVED & ACTIVE  
> **Source Target**: Unreal Engine 5.8 C++ Prototype (`Source/SURFKINI/`)  
> **Destination Target**: Godot 4.7.1 Typed GDScript (`SURFKINI-Godot/game/core/`)

---

## 1. Class & File Mapping Table

| Unreal Engine C++ Class | Godot GDScript Equivalent Class | File Location |
| :--- | :--- | :--- |
| `USurfMovementComponent` | `SurfPhysicsSolver` / `SurfController` | `game/core/movement/surf_physics_solver.gd` |
| `ASurfWeaponBase` | `WeaponBase` | `game/core/weapons/weapon_base.gd` |
| `USurfNetSnapshotBuffer` | `NetSnapshotBuffer` | `game/core/net/net_snapshot_buffer.gd` |
| `ASurfTestMapBuilder` | `RampGenerator` | `game/core/world/ramp_generator.gd` |
| `USurfTimerStateMachine` | `SurfTimer` | `game/core/meta/surf_timer.gd` |
| `USpeedMeterWidget` | `Speedometer` / `HUD` | `game/presentation/ui/speedometer.gd` |
| `USurfMassProcessor` | `BotSurfController` | `game/core/ai/bot_surf_controller.gd` |

---

## 2. Type & API Translation Rules

1. `FVector` $\rightarrow$ `Vector3`
2. `FRotator` $\rightarrow$ `Vector3` (Euler angles in radians/degrees)
3. `FMath::Clamp()` $\rightarrow$ `clampf()` / `clampi()`
4. `GetWorld()->GetDeltaSeconds()` $\rightarrow$ `delta_time: float` parameter
5. `UFUNCTION(BlueprintCallable)` $\rightarrow$ GDScript `func`
