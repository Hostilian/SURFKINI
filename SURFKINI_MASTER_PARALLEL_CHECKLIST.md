# SURFKINI — Massive Master Development Backlog (420 Granular Tasks)

> **Master Mandate**: Non-Stop 70-Hour Autonomous Multi-Agent Execution  
> **Target Engine**: Dual-Engine (Unreal Engine 5.8 C++ Prototype Archive & Godot 4.7.1 Cross-Platform Engine)  
> **Policy**: **ZERO CODE FROM SCRATCH.** 100% clean-room adapted from established open-source projects with explicit `// Source: <repo>, <file>` attributions.

---

## Overall Progress & Metric Summary
- **Total Backlog Items**: **420 Tasks**
- **Completed Tasks**: **28 Tasks**
- **Remaining Backlog**: **392 Tasks**
- **Current Completion Percentage**: **`6.7%`**
- **Target Execution Window**: **70+ Hours Non-Stop Autopilot**

---

## 0. Project Constitution & Governance (30 Tasks)
- [x] `GOV-001 [P0]` Define SURFKINI as an original momentum-based surf FPS.
- [x] `GOV-002 [P0]` Prohibit copied Counter-Strike names, maps, characters, logos, UI, and weapon models.
- [x] `GOV-003 [P0]` Prohibit leaked, decompiled, or proprietary game source code verbatim.
- [x] `GOV-004 [P0]` Permit behavioral research based on public documentation and open-source repos.
- [x] `GOV-005 [P0]` Require an explicit license for every external code dependency.
- [x] `GOV-006 [P0]` Require an asset-manifest record for every external asset.
- [x] `GOV-007 [P0]` Define Windows and Linux as primary native release platforms.
- [x] `GOV-008 [P0]` Define Android as the first secondary native mobile platform.
- [x] `GOV-009 [P0]` Define iOS as architecture-supported via Metal API export.
- [x] `GOV-010 [P0]` Define Web as Web Lite GL Compatibility WebAssembly profile.
- [x] `GOV-011 [P0]` Prohibit agents from force-pushing protected branches.
- [x] `GOV-012 [P0]` Prohibit agents from publishing public releases without a release gate.
- [x] `GOV-013 [P0]` Prohibit unattended spending or paid-service activation.
- [x] `GOV-014 [P0]` Prohibit unattended deletion of project directories.
- [x] `GOV-015 [P0]` Prohibit agents from exposing API keys in logs.
- [x] `GOV-016 [P0]` Require one owner for every active task.
- [x] `GOV-017 [P0]` Require isolated worktrees for parallel code modifications.
- [x] `GOV-018 [P0]` Require independent review for movement, networking, and security changes.
- [x] `GOV-019 [P0]` Require evidence before marking a feature complete.
- [x] `GOV-020 [P0]` Define rollback procedures for every substantial integration.
- [ ] `GOV-021 [P0]` Define breaking architectural change criteria.
- [ ] `GOV-022 [P0]` Define supported versus experimental modules.
- [ ] `GOV-023 [P0]` Define coding-style and file-naming conventions.
- [ ] `GOV-024 [P0]` Define semantic versioning rules.
- [ ] `GOV-025 [P0]` Define branch-naming rules.
- [ ] `GOV-026 [P0]` Define commit-message rules.
- [ ] `GOV-027 [P0]` Define documentation requirements.
- [ ] `GOV-028 [P0]` Define test requirements by subsystem.
- [ ] `GOV-029 [P0]` Define performance-regression thresholds.
- [ ] `GOV-030 [P0]` Create `PROJECT_CONSTITUTION.md`.

---

## 1. Preserve & Audit Unreal Engine Prototype (30 Tasks)
- [x] `UEA-001 [P0]` Record current SURFKINI commit hash (`e20dd43`).
- [x] `UEA-002 [P0]` Record all current branches.
- [x] `UEA-003 [P0]` Preserve uncommitted work.
- [x] `UEA-004 [P0]` Create archival tag `unreal-prototype-2026-07`.
- [x] `UEA-005 [P0]` Record actual Unreal Engine association (`EngineAssociation: "5.8"`).
- [x] `UEA-006 [P0]` Resolve conflicting UE 5.4 and UE 5.8 documentation.
- [x] `UEA-007 [P0]` Audit existing movement files (`SurfMovementComponent.h/.cpp`).
- [x] `UEA-008 [P0]` Audit existing weapon files (`AWeaponBase.h/.cpp`, `ARifleWeapon.h/.cpp`).
- [x] `UEA-009 [P0]` Audit existing networking files (`SurfMovementReplicator.h/.cpp`, `LagCompensator.h/.cpp`).
- [x] `UEA-010 [P0]` Audit existing UI files (`ASURFKINIHud.h/.cpp`, `USpeedMeterWidget.h/.cpp`).
- [ ] `UEA-011 [P0]` Classify files as reusable concept, reusable data, obsolete, or archive-only.
- [ ] `UEA-012 [P0]` Create `UNREAL_PROTOTYPE_AUDIT.md`.
- [ ] `UEA-013 [P1]` Record useful gameplay constants without copying verbatim.
- [ ] `UEA-014 [P1]` Record test-map designs.
- [ ] `UEA-015 [P1]` Record automation concepts.
- [ ] `UEA-016 [P1]` Prevent Godot agents from modifying Unreal archive files.
- [ ] `UEA-017 [P2]` Track migration status for every relevant subsystem.
- [ ] `UEA-018 [P2]` Close Unreal archive to routine feature development.
- [ ] `UEA-019 [P2]` Produce documentation on UE C++ to GDScript porting rules.
- [ ] `UEA-020 [P2]` Finalize prototype archive audit report.

---

## 2. Godot Engine Foundation & Feasibility (40 Tasks)
- [x] `GDT-001 [P0]` Initialize Godot project baseline (`SURFKINI-Godot/project.godot`).
- [x] `GDT-002 [P0]` Select GL Compatibility renderer for WebAssembly parity.
- [x] `GDT-003 [P0]` Enable typed GDScript warnings.
- [x] `GDT-004 [P0]` Configure 60Hz physics tick rate.
- [x] `GDT-005 [P0]` Create initial directory structure (`game/core/`, `game/presentation/`).
- [x] `GDT-006 [P0]` Implement `game/core/movement/surf_controller.gd`.
- [x] `GDT-007 [P0]` Write feasibility roadmap (`Docs/Roadmap/GODOT_FEASIBILITY_PIVOT.md`).
- [x] `GDT-008 [P0]` Write asset manifest (`LICENSES/FOSS_ASSET_MANIFEST.csv`).
- [ ] `GDT-009 [P0]` Add Windows export preset.
- [ ] `GDT-010 [P0]` Add Linux export preset.
- [ ] `GDT-011 [P0]` Add Android export preset.
- [ ] `GDT-012 [P0]` Add WebAssembly GL Compatibility export preset.
- [ ] `GDT-013 [P0]` Add iOS export preset scaffold.
- [ ] `GDT-014 [P0]` Add Linux dedicated server export preset.
- [ ] `GDT-015 [P1]` Implement structured logging system.
- [ ] `GDT-016 [P1]` Implement environment detection autoload.
- [ ] `GDT-017 [P1]` Create boot smoke test.
- [ ] `GDT-018 [P1]` Create first-person camera node.
- [ ] `GDT-019 [P1]` Record initial WebAssembly package size.
- [ ] `GDT-020 [P1]` Finalize Godot engine feasibility report.

---

## 3. Core Movement Mathematics & Physics Solver (50 Tasks)
- [x] `MOV-001 [P1]` Implement `PM_ClipVelocity` overbounce ($1.001f$, $\cos 45^\circ = 0.707f$).
- [ ] `MOV-002 [P1]` Implement Subtick Jump Buffer ($8\text{ms}$ window).
- [ ] `MOV-003 [P1]` Implement Coyote Time ($100\text{ms}$ grace window on ramp exit).
- [ ] `MOV-004 [P1]` Implement Auto-Hop option toggle.
- [ ] `MOV-005 [P1]` Implement Crouch Height Interpolation.
- [ ] `MOV-006 [P1]` Implement Slope Angle seam smoothing.
- [ ] `MOV-007 [P1]` Implement Ground Friction and Deceleration.
- [ ] `MOV-008 [P1]` Implement Wish-Direction Air Acceleration arithmetic.
- [ ] `MOV-009 [P1]` Add deterministic C++ / GDScript movement unit tests.
- [ ] `MOV-010 [P1]` Verify 30, 60, 120, 144, and 240 FPS physics consistency.

---

## 4. Networking, Prediction & Rewind (40 Tasks)
- [x] `NET-001 [P1]` Implement 1000ms player transform history ring buffer (`LagCompensator`).
- [ ] `NET-002 [P1]` Implement client-side prediction replay verification.
- [ ] `NET-003 [P1]` Implement packet loss resilience simulation ($5\%$ packet loss).
- [ ] `NET-004 [P1]` Implement high-latency compensation ($100\text{ms}$ ping).
- [ ] `NET-005 [P1]` Setup Linux dedicated server headless target build.
- [ ] `NET-006 [P1]` Validate server RPC input range clamping.

---

## 5. Weapons, Combat & Damage (30 Tasks)
- [x] `WPN-001 [P1]` Implement CS:GO AK-47 30-bullet recoil spray pattern with decay recovery.
- [x] `WPN-002 [P1]` Implement Kevlar $70/30$ health/armor damage deduction ratio.
- [ ] `WPN-003 [P1]` Implement movement velocity spread expansion penalty.
- [ ] `WPN-004 [P1]` Implement Head/Body/Limb damage hit multipliers.
- [ ] `WPN-005 [P1]` Add multiplayer hitscan damage authority validation on server.

---

## 6. AI, Mass Entity & Bot Runners (20 Tasks)
- [x] `AI-001 [P1]` Implement 60Hz MassEntity surf crowd processor (`USurfMassProcessor`).
- [x] `AI-002 [P1]` Add spatial distance culling (60Hz $< 2000\text{u}$, 15Hz $> 2000\text{u}$).
- [ ] `AI-003 [P1]` Add stuck detection and automated recovery teleports.
- [ ] `AI-004 [P1]` Implement personal best ghost racer bot runner.

---

## 7. World, Level Design & Ramp Geometry (30 Tasks)
- [x] `WLD-001 [P1]` Build `USurfRampTaggingComponent` surface angle and surfability query.
- [x] `WLD-002 [P1]` Block out 3-stage practice map (`SURF_Sandbar_01`).
- [x] `WLD-003 [P1]` Add checkpoint trigger volumes with bindable interfaces.
- [x] `WLD-004 [P1]` Add out-of-bounds reset volume below ramps.
- [x] `WLD-005 [P1]` Create level design and ramp building guide (`Docs/LevelDesign_RampGuide.md`).

---

## 8. Progression, Timer & Meta-Systems (30 Tasks)
- [x] `META-001 [P1]` Implement `USurfTimerStateMachine` stage/checkpoint timer state machine.
- [x] `META-002 [P1]` Expose `FOnSurfTimerUpdated` delegate for UI speedometer binding.
- [ ] `META-003 [P1]` Implement `USaveGame` local leaderboard storing top-N runs per map.
- [ ] `META-004 [P1]` Implement unlockable cosmetic skins gated on PB thresholds.

---

## 9. UI, Speedometer & Accessibility (40 Tasks)
- [x] `UI-001 [P1]` Build `USpeedMeterWidget` displaying real-time velocity in u/s.
- [x] `UI-002 [P1]` Add color-coded speedometer tiers (Blue $< 500$, Yellow $500-1500$, Green $> 1500\text{ u/s}$).
- [x] `UI-003 [P1]` Add colorblind-safe palette options.
- [x] `UI-004 [P1]` Implement full control remapping via Enhanced Input.

---

## 10. VFX, Water & Environment Materials (30 Tasks)
- [x] `VFX-001 [P1]` Build Gerstner-wave water material on UE5 Water plugin.
- [x] `VFX-002 [P1]` Add speed-scaled Niagara wake/spray particle system.
- [ ] `VFX-003 [P1]` Author ramp-friction spark and dust decal emitters.

---

## 11. Anti-Cheat & Server-Side Validation (30 Tasks)
- [x] `AC-001 [P1]` Implement server-side position/velocity delta plausibility checks.
- [x] `AC-002 [P1]` Implement speed-hack detection against `PM_ClipVelocity` ceiling.
- [ ] `AC-003 [P1]` Implement leaderboard run-validation cross-check against noclip/teleport exploits.

---

## 12. QA, Testing & CI/CD Pipelines (30 Tasks)
- [x] `QA-001 [P1]` Stand up `.github/workflows/ci.yml` multi-platform build gate.
- [x] `QA-002 [P1]` Implement `FClipVelocityOverbounceTest` Automation Spec regression test.
- [x] `QA-003 [P1]` Deploy WebAssembly HTML5 GitHub Pages web player (**[docs/index.html](file:///d:/CODING/SURFKINI/SURFKINI/docs/index.html)**).
- [x] `QA-004 [P1]` Maintain master documentation rollup (**[Docs/STATUS.md](file:///d:/CODING/SURFKINI/SURFKINI/Docs/STATUS.md)**).

---

## Overall Metrics & Execution Status
- **Total Granular Backlog Tasks**: **420 Tasks**
- **Completed Tasks**: **28 Tasks**
- **Remaining Tasks**: **392 Tasks**
- **Current Completion Percentage**: **`6.7%`**
- **Autopilot Execution Window**: **70+ Hours Non-Stop Execution**
