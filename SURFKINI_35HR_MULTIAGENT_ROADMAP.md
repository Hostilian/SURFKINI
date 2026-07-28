# SURFKINI — 35-Hour Autonomous Multi-Agent Operational Roadmap

> **System Architecture**: Multi-Agent Parallel Worktree Infrastructure  
> **Target Engine**: Unreal Engine 5.8 (C++)  
> **Orchestrator**: `surfkini_orchestrator.py`  
> **Baseline References**: Valve Source SDK 2013 (`gamemovement.cpp`), EricXu1728/Godot4SourceEngineMovement (MIT), Gabriel Gambetta Multiplayer Prediction Architecture, ENet Reliable UDP, UE5 MassEntity.

---

## 1. Executive Summary & Parallel Execution Strategy

The SURFKINI multi-agent architecture runs 5 parallel sub-agents across isolated Git worktrees (`movement`, `weapons`, `ai`, `net`, `ui`). 
To ensure continuous execution over a 35+ hour operating window, tasks are organized into 7 sequential phases (5 hours each) with explicit fallback mechanisms and zero-regression rules.

```
       ┌───────────────────────────────────────────────────────────┐
       │             surfkini_orchestrator.py (Master)             │
       └─────┬───────────┬───────────┬─────────────┬───────────┬───┘
             │           │           │             │           │
             ▼           ▼           ▼             ▼           ▼
       ┌───────────┐┌───────────┐┌───────────┐┌───────────┐┌───────────┐
       │  Agent 1  ││  Agent 2  ││  Agent 3  ││  Agent 4  ││  Agent 5  │
       │ Movement  ││  Weapons  ││    Net    ││    AI     ││    UI     │
       └───────────┘└───────────┘└───────────┘└───────────┘└───────────┘
```

---

## 2. Agent Assignments & Open-Source References

| Agent | Worktree Branch | Primary Module | Open-Source Reference Baseline |
| :--- | :--- | :--- | :--- |
| **Agent 1: Movement** | `surfkini-worktrees-movement` | `Source/SURFKINI/Movement/` | `ValveSoftware/source-sdk-2013` (`gamemovement.cpp`), `EricXu1728/Godot4SourceEngineMovement` |
| **Agent 2: Weapons** | `surfkini-worktrees-weapons` | `Source/SURFKINI/Weapons/` | `ValveSoftware/csgo-vpk` weapon recoil tables, `Quake III Arena` weapon prediction |
| **Agent 3: Net** | `surfkini-worktrees-net` | `Source/SURFKINI/Net/` | `Gabriel Gambetta` Fast-Paced Multiplayer, `lsquic` / `ENet` UDP reliable socket architecture |
| **Agent 4: AI Mass** | `surfkini-worktrees-ai` | `Source/SURFKINI/AI/` | `UnrealEngine MassEntity` sample architecture, `ONNX Runtime` C++ interface |
| **Agent 5: UI & HUD** | `surfkini-worktrees-ui` | `Source/SURFKINI/UI/` | `SurfTimer` CS:GO HUD layout, `Slate` / `UMG` dynamic graphics rendering |

---

## 3. 35-Hour Master Task Matrix

### Phase 1: Core Systems & High-Frequency Synchronization (Hours 0–5)
- [x] **Movement**: Implement `ClipVelocity` with overbounce (`1.001f`) & normal smoothing (`SmoothFacetNormal`).
- [x] **Weapons**: Base weapon hierarchy (`AWeaponBase`, `ARifleWeapon`, `AProjectileWeapon`).
- [x] **Net**: Implement 1000ms ring buffer in `LagCompensator`.
- [x] **AI**: Implement `SurfMassProcessor` 60Hz tick pipeline.
- [x] **UI**: Create `SpeedMeterWidget` (u/s display) and `SURFKINIHud` canvas crosshair.

### Phase 2: Advanced Physics & Weapon Mechanics (Hours 5–10)
- [ ] **Movement**: Subtick Jump Buffer (8ms window) & Coyote Time (100ms grace window).
- [ ] **Weapons**: Dynamic recoil tables (CS:GO AK-47 style 30-bullet spray pattern with recovery decay curve).
- [ ] **Net**: Client-side prediction replay buffer with error thresholds ($> 2.0\text{ cm}$).
- [ ] **AI**: MassEntity crowd collision avoidance on ramps ($Z \ge 0.707$).
- [ ] **UI**: Dynamic crosshair expansion scaling with current velocity and weapon spread angle.

### Phase 3: Network Rewind & Armor Damage Systems (Hours 10–15)
- [ ] **Movement**: Ramp seam anti-snag raycast smoothing & Overbounce trick calculation ($V_{\text{overbounce}} = \vec{v} - 2(\vec{v} \cdot \hat{n})\hat{n}$).
- [ ] **Weapons**: Kevlar + Helmet armor degradation math ($70\%$ health ratio, $30\%$ armor depletion).
- [ ] **Net**: Server-side hitbox rewind verification for hitscan raycasts.
- [ ] **AI**: Behavior Tree tasks for strafe-shooting while maintaining surf ramp momentum.
- [ ] **UI**: Real-time Surf Timer displaying checkpoint splits, delta time, and PB ghost telemetry.

### Phase 4: Projectile Prediction & High-Density Mass AI (Hours 15–20)
- [ ] **Movement**: Water/Ladder surf transition states (`MOVE_Water`, `MOVE_Ladder`).
- [ ] **Weapons**: Fast-moving plasma projectile predictive extrapolation ($X(t) = X_0 + V_0 t + \frac{1}{2}a t^2$).
- [ ] **Net**: Bandwidth-optimized delta compression for player movement transforms (quantized 16-bit vectors).
- [ ] **AI**: Scale `SurfMassProcessor` to 1,000 active entities with LOD tick budgeting (60Hz near, 15Hz far).
- [ ] **UI**: Killfeed notification stack with weapon icons, headshot indicators, and wallbang badges.

### Phase 5: Anti-Cheat & Graceful Degradation (Hours 20–25)
- [ ] **Movement**: Speed cap verification (Bhop max speed cap $300\text{ u/s}$ unless surfing).
- [ ] **Weapons**: Server-authoritative fire rate throttling (666 RPM enforcement).
- [ ] **Net**: Connection loss graceful degradation — interpolation buffer fallback ($100\text{ms}$ buffer under packet loss).
- [ ] **AI**: Squad Leader ONNX model loader interface for tactical AI decision trees.
- [ ] **UI**: Scoreboard layout displaying ping, K/D/A, surf completion times, and team economic state.

### Phase 6: Map Telemetry & Sound Physics (Hours 25–30)
- [ ] **Movement**: Sound triggers for land impact, surf ramp friction sliding audio, and wind shear.
- [ ] **Weapons**: Sound attenuation & spatial 3D audio positional rendering for gunfire.
- [ ] **Net**: Dedicated server headless mode CLI arguments (`-log`, `-mode=server`, `-port=7777`).
- [ ] **AI**: Meso-agent NPC pathing across complex multi-ramp surf courses (`SurfRampTestMap`).
- [ ] **UI**: Main menu & settings UI with FOV slider ($90^\circ - 120^\circ$), sensitivity scaling, and audio volume controls.

### Phase 7: Optimization, Polish & Automated Verification (Hours 30–35)
- [ ] **Movement**: Memory alignment optimization (`alignas(16)` SIMD vector operations for `ClipVelocity`).
- [ ] **Weapons**: Bullet hole decal spawning & hit impact particle VFX pooling.
- [ ] **Net**: Replay system — recording tick history to `.demo` files for instant replay.
- [ ] **AI**: Performance benchmarking — 2,000 Mass entities at $> 60\text{ FPS}$.
- [ ] **UI**: Complete HUD visual polish (glassmorphism accents, neon speed indicators, dark mode styling).

---

## 4. Graceful Degradation & Resilience Guardrails

1. **Build Verification Rule**: No agent may merge code into `main` without passing `Build.bat SURFKINIEditor Win64 Development`.
2. **Include Order Rule**: All headers must use `#include "CoreMinimal.h"` and explicit module paths (`PublicIncludePaths.Add(ModuleDirectory);`).
3. **Network Fallback**: If server latency exceeds $250\text{ms}$, client falls back to local visual prediction smoothing to prevent rubberbanding.
4. **AI Performance Fallback**: If frame rate drops below $60\text{ FPS}$, `SurfMassProcessor` automatically drops far-LOD entity ticks from 15Hz to 5Hz.

---

## 5. Execution Command

To execute all 5 parallel agents, run the orchestrator script:
```powershell
python surfkini_orchestrator.py
```
Or launch individual agent prompts from **`FCC_CLAUDE_PARALLEL_PROMPT.md`**.
