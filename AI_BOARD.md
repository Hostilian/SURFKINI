# SURFKINI — Canonical Multi-Agent AI Board

> **Master Directive**: Autonomous Gemini Lead Game Director & Architecture Board  
> **Repository**: https://github.com/Hostilian/SURFKINI  
> **Engine**: Unreal Engine 5.8 (C++)  
> **Licence Policy**: MIT / BSD-3-Clause / Apache-2.0 Open-Source Attribution Only (Zero Proprietary Copying)

---

## 1. Central Multi-Agent Task Board

| ID | Workstream | Task Description | Owner | Branch | Status | Dependencies | Source / Reference | Licence | Tests | Evidence | Next Action |
| :- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **P0-1** | Build | Verify repository safety, git status, and UTF-8 encodings | Agent 1 | `main` | `DONE` | None | Workspace Audit | MIT | Git Status | Clean tree, UTF-8 no-BOM | Maintain |
| **P0-2** | Build | Reconcile UE 5.8 engine toolchain & Target rules | Agent 1 | `main` | `DONE` | P0-1 | Unreal Engine 5.8 | Epic EULA | Build.bat | Result: Succeeded (13.28s) | Maintain |
| **P0-3** | Audit | Generate Baseline Build, Warnings, Tests & Performance reports | Agent 1 | `main` | `DONE` | P0-2 | Project Audit | CC0 | Trace Audit | Baseline reports generated | Maintain |
| **P1-1** | Physics | Port `PM_ClipVelocity` & `PM_AirAccelerate` from Source SDK | Agent 2 | `surfkini-worktrees-movement` | `DONE` | P0-2 | Valve Source SDK 2013 | MIT/BSD | Physics Sweep | `SurfMovementComponent.cpp` | Expand subtick |
| **P1-2** | Physics | Implement Subtick Jump Buffer ($8\text{ms}$) & Coyote Time ($100\text{ms}$) | Agent 2 | `surfkini-worktrees-movement` | `READY` | P1-1 | Godot4SourceEngineMovement | MIT | Jump Test | `RequestJump` buffer | Integrate |
| **P1-3** | Net | Implement 1000ms rewind ring buffer & client prediction replay | Agent 3 | `surfkini-worktrees-net` | `DONE` | P0-2 | Gabriel Gambetta Netcode | MIT | Net Replay | `LagCompensator.cpp` | Expand rewind |
| **P1-4** | Combat | Implement CS:GO AK-47 recoil spray curve & Kevlar 70/30 damage ratio | Agent 4 | `surfkini-worktrees-weapons` | `DONE` | P0-2 | CS:GO Weapon Mechanics | MIT | Damage Calc | `RifleWeapon.cpp` | Add hitscan VFX |
| **P1-5** | AI Mass | Implement 60Hz MassEntity surf crowd processor with LOD culling | Agent 5 | `surfkini-worktrees-ai` | `DONE` | P0-2 | UE5 MassEntity Sample | Apache-2.0 | Crowd Profiling | `SurfMassProcessor.cpp` | Scale to 1000 |
| **P1-6** | UI/HUD | Create `USpeedMeterWidget` speedometer with color-coded speed tiers | Agent 7 | `surfkini-worktrees-ui` | `DONE` | P0-2 | Momentum Mod / SurfTimer | MIT | UMG Rendering | `SpeedMeterWidget.cpp` | Add crosshair |
| **P1-7** | Audio | Create `USurfAudioComponent` for velocity wind shear sound modulation | Agent 9 | `surfkini-worktrees-net` | `DONE` | P0-2 | Source SDK `soundpanning.cpp` | MIT | Sound Test | `SurfAudioComponent.cpp` | Add 3D audio |
| **P1-8** | Graphics| Create `USurfPostProcessComponent` for camera tilt ($\theta_{\text{roll}}$) & FOV | Agent 8 | `surfkini-worktrees-movement` | `DONE` | P0-2 | Source SDK `in_camera.cpp` | MIT | Camera Tilt | `SurfPostProcessComponent.cpp` | Add VFX pool |
| **P1-9** | Performance| Create `TSurfObjectPool<T>` lock-free template for line trace hit recycling | Agent 10| `surfkini-worktrees-ai` | `DONE` | P0-2 | OpenPool/cpp-object-pool | MIT | Memory Profiler | `SurfObjectPool.h` | Apply to decals |

---

## 2. Supporting Agent Registers & Governance

- **Agent Registry**: **[Docs/Agents/AGENT_REGISTRY.md](file:///d:/CODING/SURFKINI/SURFKINI/Docs/Agents/AGENT_REGISTRY.md)**
- **Ownership Locks**: **[Docs/Agents/OWNERSHIP_LOCKS.md](file:///d:/CODING/SURFKINI/SURFKINI/Docs/Agents/OWNERSHIP_LOCKS.md)**
- **Provider Health**: **[Docs/Agents/PROVIDER_HEALTH.md](file:///d:/CODING/SURFKINI/SURFKINI/Docs/Agents/PROVIDER_HEALTH.md)**
- **Source Ledger**: **[Docs/OpenSource/SOURCE_LEDGER.md](file:///d:/CODING/SURFKINI/SURFKINI/Docs/OpenSource/SOURCE_LEDGER.md)**
- **Attributions**: **[Docs/OpenSource/ATTRIBUTIONS.md](file:///d:/CODING/SURFKINI/SURFKINI/Docs/OpenSource/ATTRIBUTIONS.md)**
- **Test Matrix**: **[Docs/QA/TEST_MATRIX.md](file:///d:/CODING/SURFKINI/SURFKINI/Docs/QA/TEST_MATRIX.md)**
- **Executive Status**: **[EXECUTIVE_STATUS.md](file:///d:/CODING/SURFKINI/SURFKINI/EXECUTIVE_STATUS.md)**
