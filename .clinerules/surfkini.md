# SURFKINI — Cline Memory Bank
#
# Cline re-reads this file at the start of every session.
# Keep it current.

## Project Identity

- **Project**: SURFKINI — CS/Source-style surf FPS built in Unreal Engine 5
- **Engine**: Unreal Engine 5.4 (C++ primary, Blueprints for prototyping)
- **Language**: C++20 (UE-style), with Blueprint visual scripting
- **Platform Targets**: Windows (primary), Linux dedicated server, potentially console
- **Architecture Style**: See the big technical spec in the docs/ folder

## AI Toolchain (FCC)

- **FCC Server**: `http://127.0.0.1:8082` — must be running before using Cline
- **Token**: `freecc`
- **Models available**: NVIDIA NIM llama-3.3-70b, Groq, OpenRouter, Gemini, etc.
- **Start server**: run `fcc-server.bat` or `Start-SURFKINI.ps1`

## Coding Rules for This Project

### Unreal Engine C++ Conventions
- All classes must follow UE naming: `U` prefix for UObject, `A` for AActor, `F` for structs, `E` for enums
- Use `UPROPERTY()`, `UFUNCTION()`, `UCLASS()` macros correctly
- Never use `new` / `delete` directly — use `NewObject<T>()`, `SpawnActor<T>()`, `MakeShared<T>()`
- All UObjects must be GC-safe (store in UPROPERTY or weak pointers)
- Use `FVector`, `FRotator`, `FQuat` — never raw floats for transforms

### Movement Physics (Core Gameplay)
- Air acceleration: Source/Quake-style (wish_direction dot velocity capping, not raw speed cap)
- Ramp sliding: custom `ClipVelocity()` via `move_and_collide` loop, NOT Unreal's default `CharacterMovementComponent` slope handling
- Physics tick: locked 60Hz in `TickComponent`, visual interpolation in separate `_process` equivalent
- Surface threshold: `SurfaceNormal.Z >= 0.707` (cos 45°) for walkable vs slideable

### Architecture Rules
- Movement logic lives in `Source/SURFKINI/Movement/` — NEVER in Blueprint
- Do NOT modify `.uproject` file directly — let UBT manage it
- Never hardcode paths — use `FPaths::ProjectDir()`, `FPaths::EngineDir()`
- Server-authoritative: all physics runs on server, client predicts + reconciles

### File Organization
```
Source/SURFKINI/
  Movement/          <- All surf physics code here
  Weapons/           <- Weapon actors
  Characters/        <- Player + NPC classes
  AI/                <- Behavior trees, agent classes
  UI/                <- HUD, menus
  Net/               <- Networking, replication helpers
Content/             <- Blueprints, assets (no logic here)
```

### What NOT to Do
- Do NOT copy code from Valve's Source SDK 2013 — use clean-room reimplementation
- Do NOT use `bhop3d` Godot repo (AGPL-3.0 — viral copyleft)
- Do NOT put gameplay logic in Blueprints — prototype there, then port to C++
- Do NOT commit `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/` — they're gitignored

## Current Status

- [ ] UE5 project files generated
- [ ] Movement base class scaffolded
- [ ] FCC AI server connected

## Key Technical Decisions

- Custom kinematic movement loop (bypasses UCharacterMovementComponent)
- Server-authoritative with client prediction + rollback
- Mass AI framework for large NPC crowds
- ENet for native, WebRTC for browser clients (if web export needed)
