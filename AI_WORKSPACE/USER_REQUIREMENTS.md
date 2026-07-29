# SURFKINI — USER REQUIREMENTS SPECIFICATION

- **REQ-001**: Source air-strafing, `PM_ClipVelocity`, 100ms Coyote Time, 8ms subtick jump buffer.
- **REQ-002**: Kinetic wall collision damage formula: $Damage = k \cdot (v_{\text{impact}} - v_{\text{threshold}})^2$.
- **REQ-003**: Left/Right wall-running trace sweeps, low/high obstacle vaulting, and ledge mantling.
- **REQ-004**: Dual FPP/TPP camera system with collision-safe SpringArm and 'V' key toggle.
- **REQ-005**: AK-47 recoil decay patterns, Kevlar 70/30 damage reduction, hitscan and projectile trajectories.
- **REQ-006**: Modular Speed Thrusters and Armor Plate loadout/gear system (`USurfGearSystem`).
- **REQ-007**: 64/128 tickrate dedicated server loops, client prediction, and 1000ms lag compensation rewind (`ULagCompensator`).
- **REQ-008**: In-app runtime level editor object placement, grid snapping, and `.json` map schema export/import (`ASurfRuntimeLevelEditor`).
- **REQ-009**: Steam Workshop API publishing and downloading wrappers (`USurfSteamWorkshop`).
- **REQ-100**: Tier 1 data mods, mutators, and server ruleset manifests (`USurfModSystem`).
- **REQ-101**: Realtime speedometer (u/s), strafe-sync indicator (%), health/armor bars, ammo counter (`USurfHUDWidget`).
- **REQ-102**: 18-Suite Automated QA Unit Test Suite (`run_tests.py` v9.0.0).
