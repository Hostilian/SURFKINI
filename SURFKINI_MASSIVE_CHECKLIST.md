# SURFKINI — Exhaustive Master Checklist & Production Roadmap
## Unreal Engine 5.4 | Massive Parallel AI Agent CS-Surf Shooter

> **Project Identity**: SURFKINI | **Engine**: Unreal Engine 5.4+ (C++20) | **AI Proxy**: FCC Port 8082

---

## 🎯 Executive Overview & Master Verification Matrix

This checklist tracks every engineering requirement, math formula, C++ module, AI agent tier, network RPC, and compliance gate across the SURFKINI project.

---

## 📌 Pillar 1: Core Engine & VS Code / AI Infrastructure Scaffold

- [x] UE5.4 `.uproject` descriptor created (`SURFKINI.uproject`)
- [x] `Config/DefaultEngine.ini` configured (60Hz physics tick, WASD + Mouse bindings, substepping enabled)
- [x] `Config/DefaultGame.ini` configured (`SURFKINIGameMode` set as default pawn and server game mode)
- [x] `Source/SURFKINI.Target.cs` created (BuildSettingsVersion.V4, IncludeOrderVersion.Unreal5_4)
- [x] `Source/SURFKINIEditor.Target.cs` created (Development Editor target)
- [x] `Source/SURFKINI/SURFKINI.Build.cs` created (EnhancedInput, NetCore, PhysicsCore, UMG)
- [x] `Source/SURFKINI/SURFKINI.cpp` created (`IMPLEMENT_PRIMARY_GAME_MODULE`)
- [x] `.vscode/settings.json` configured (Watcher exclusions for `Binaries/`, `Intermediate/`, `Saved/`)
- [x] `.vscode/c_cpp_properties.json` configured (UE 5.4 headers & MSVC x64 IntelliSense)
- [x] `.vscode/tasks.json` configured (`Ctrl+Shift+B` default build, shipping, clean, generate project files)
- [x] `.vscode/extensions.json` configured (C++ tools, Cline, LLDB, Git Graph)
- [x] Launchers created: `fcc-claude.bat`, `fcc-server.bat`, `Start-SURFKINI.ps1`
- [x] Cline Memory Bank initialized (`.clinerules/surfkini.md`)
- [x] `.gitignore` configured for UE5
- [x] `surfkini_orchestrator.py` created & tested (manages isolated Git worktrees)
- [x] Worktrees generated (`agent/movement`, `agent/weapons`, `agent/ai`, `agent/net`, `agent/ui`)
- [x] FCC AI proxy model routing upgraded (`Claude 3.5 Sonnet`, `DeepSeek-R1`, `DeepSeek V3` with reasoning)
- [x] 84 Skills & Knowledge items imported into `.agents/skills/` & `.agents/knowledge/`

---

## 🏄 Pillar 2: Mathematics & Physics Simulation (CS/Source Surf Engine)

- [x] `SurfMovementComponent.h/.cpp` scaffolded
- [x] Clean-room `ClipVelocity` implementation (overbounce coefficient = `1.001f`)
- [x] Air acceleration formula with perpendicular wish-direction projection cap (`AirSpeedCap = 30.0f` ups)
- [x] Surface threshold classification: `HitNormal.Z >= 0.707f` (cos 45°) for ground vs surf ramp
- [x] Quake-style ground friction with `StopSpeed` threshold
- [x] Anti-tunneling sub-stepping (`SubSteps = ceil(speed * dt / capsule_radius)`)
- [x] Deterministic 60Hz fixed-tick accumulator
- [x] 128-entry `FSurfSavedMove` client prediction ring buffer
- [ ] Implement subtick jump buffering (8ms window to prevent dropped spacebar inputs)
- [ ] Implement coyote time (100ms grace window after leaving ground or ramp edges)
- [ ] Implement normal interpolation between consecutive contact facets to eliminate edge-snagging
- [ ] Implement customizable speed caps per surface region (ramp speed zone triggers)
- [ ] Implement wall-run and ramp-jump velocity boost mechanics

---

## 🔫 Pillar 3: Weapons, Ballistics & Combat Architecture

- [x] `WeaponBase.h/.cpp` created (Abstract base class for ammo, fire rate, recoil, fire modes)
- [x] `RifleWeapon.h/.cpp` created (Hitscan rifle, 666 RPM, 35 Base Damage, 100m range)
- [x] `ProjectileWeapon.h/.cpp` created (Physics plasma projectile launcher)
- [x] CS-style armor damage absorption math (100 HP + 100 Armor, 70% armor ratio)
- [ ] Implement weapon recoil patterns (pitch/yaw spray tables)
- [ ] Implement weapon spread and inaccuracy scaling based on movement speed
- [ ] Implement weapon switching animations and holster timers
- [ ] Implement ammo pickup actors and weapon drop mechanics
- [ ] Implement hit notification sounds and damage indicators

---

## 🎯 Pillar 4: Lag Compensation & Server-Authoritative Hitbox Rewind

- [x] `LagCompensator.h/.cpp` created (1000ms ring buffer of historical player transforms)
- [ ] Implement `RewindActor` function (interpolates transform buffer to client fire timestamp)
- [ ] Implement `RestoreActor` function (resets target actor to current server location)
- [ ] Implement server-authoritative line trace against rewound player capsule hitboxes
- [ ] Implement anti-cheat validation: reject shots with timestamps older than 500ms or future timestamps

---

## 🤖 Pillar 5: Massive Parallel AI Agent Hierarchy

- [x] Micro-Agent Specification: 10,000+ Niagara GPU particle bullets and physics debris
- [x] Meso-Agent Specification: 500+ surf NPCs using `UMassEntity` + `USurfMassProcessor`
- [x] Macro-Agent Specification: 10 Squad Leaders using ONNX neural inference
- [x] Meta-Agent Specification: World Manager for procedural difficulty scaling
- [x] `SurfMassProcessor.h/.cpp` created (Mass Entity surf physics processor)
- [x] `SurfEnemyController.h/.cpp` created (Behavior Tree AI Controller for surf NPCs)
- [ ] Implement Niagara compute shader particle collision and ricochet dynamics
- [ ] Implement ONNX model runtime integration in C++ for Macro-agent tactical decision making
- [ ] Implement Meta-agent dynamic wave spawner and dynamic obstacle manager

---

## 🌐 Pillar 6: Networking, ENet Transport & Client Prediction / Rollback

- [x] `SurfMovementReplicator.h/.cpp` created (Server authority & prediction reconciliation)
- [ ] Implement `ServerSendMove` RPC validation and execution
- [ ] Implement `ClientCorrectState` RPC for position error > 0.005 units
- [ ] Implement client-side rollback & re-simulation loop from saved input buffer
- [ ] Integrate ENet UDP transport layer for native Windows/Linux clients
- [ ] Implement Nakama matchmaking and dynamic server container orchestration integration

---

## 🖥️ Pillar 7: UI, Speed Meter HUD & Analytics

- [x] `SpeedMeterWidget.h/.cpp` created (Displays speed in u/s and state string)
- [x] `SURFKINIHud.h/.cpp` created (Canvas renderer for crosshairs and HUD overlays)
- [ ] Implement color-coded speed tier indicators (e.g., green for >1000 u/s)
- [ ] Implement kill feed widget and spectator HUD
- [ ] Implement scoreboard widget (KDA, ping, score, surf time)
- [ ] Implement main menu UI with audio/video/controls settings

---

## ⚖️ Pillar 8: Legal, Open-Source & License Compliance Audit

- [x] Clean-room vector projection physics verified (no Valve Source SDK 2013 code used)
- [x] AGPL-3.0 copyleft risk audited (`bhop3d` repository excluded)
- [ ] Create `THIRD_PARTY.md` cataloging all open-source libraries and licenses
- [ ] Create `ASSET_MANIFEST.csv` tracking CC0 assets (Kenney, Quaternius, Poly Haven)
- [ ] Configure Git LFS for binary assets (`Content/**/*.uasset`, `Content/**/*.umap`)

---

## 🧪 Pillar 9: CI/CD, Automated Testing & Release Engineering

- [ ] Create deterministic replay file recorder (`.replay` format)
- [ ] Create automated physics regression test suite
- [ ] Create GitHub Actions workflow for build compilation checks
- [ ] Create Linux dedicated server containerization Dockerfile
