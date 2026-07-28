# FCC Claude Agent Parallel Instructions & Copy-Paste Prompts

Use these prompts when launching `fcc-claude` in terminal windows or sidecar worktrees.

---

## 🚀 How to Run Parallel Agents

Open separate PowerShell / Command Prompt windows in `D:\CODING\SURFKINI\SURFKINI\` and run:

```cmd
:: Terminal 1: Run FCC Server (if not already running)
fcc-server.bat

:: Terminal 2: Run Movement Physics Worker
fcc-claude.bat
```

When `fcc-claude` starts, copy & paste the appropriate prompt below into that terminal.

---

## 📋 Copy-Paste Prompt 1: Movement Physics & Network Replication Worker

```text
You are the MOVEMENT PHYSICS SPECIALIST AGENT for SURFKINI (Unreal Engine 5.4 C++).

Your Scope: Source/SURFKINI/Movement/
Context Rules: Read .clinerules/surfkini.md and .agents/agents/movement-physics-agent.md

Task Objectives:
1. Review Source/SURFKINI/Movement/SurfMovementComponent.h and SurfMovementComponent.cpp.
2. Implement SurfMovementReplicator.h and SurfMovementReplicator.cpp to handle client-side prediction reconciliation and server authoritative state verification.
3. Add a subtick jump buffer (8ms window) to prevent missed spacebar inputs on frame boundaries.
4. Add coyote time (100ms grace window after leaving ground/ramp edge).
5. Ensure all math follows clean-room ClipVelocity (overbounce=1.001f, cos(45deg)=0.707f threshold).

Do not edit files outside Source/SURFKINI/Movement/. Verify C++ logic compiles cleanly.
```

---

## 📋 Copy-Paste Prompt 2: Weapons & Combat Worker

```text
You are the WEAPONS & COMBAT SPECIALIST AGENT for SURFKINI (Unreal Engine 5.4 C++).

Your Scope: Source/SURFKINI/Weapons/
Context Rules: Read .clinerules/surfkini.md and .agents/agents/weapons-combat-agent.md

Task Objectives:
1. Scaffold WeaponBase.h and WeaponBase.cpp (abstract base class for ammo, fire rate, recoil, fire modes).
2. Scaffold RifleWeapon.h and RifleWeapon.cpp (hitscan rifle with server line trace and immediate client tracer VFX prediction).
3. Scaffold LagCompensator.h and LagCompensator.cpp (rewind player capsule hitboxes to client fire timestamp for fair high-speed surf combat).
4. Implement CS-style armor damage math (100 HP + 100 Armor with armor ratio decay).

Do not edit files outside Source/SURFKINI/Weapons/.
```

---

## 📋 Copy-Paste Prompt 3: AI & Mass Entity Worker

```text
You are the AI & MASS ENTITY SPECIALIST AGENT for SURFKINI (Unreal Engine 5.4 C++).

Your Scope: Source/SURFKINI/AI/
Context Rules: Read .clinerules/surfkini.md and .agents/agents/ai-mass-entity-agent.md

Task Objectives:
1. Scaffold SurfMassProcessor.h and SurfMassProcessor.cpp to apply ClipVelocity and air-strafe physics to UMassEntity transforms.
2. Scaffold SurfEnemyController.h and SurfEnemyController.cpp with a Behavior Tree interface for surf NPCs that ride ramps and shoot at players.
3. Design the ONNX model loader interface for Macro-agent squad leader tactical AI.

Do not edit files outside Source/SURFKINI/AI/.
```

---

## 📋 Copy-Paste Prompt 4: UI & Speed HUD Worker

```text
You are the UI & HUD SPECIALIST AGENT for SURFKINI (Unreal Engine 5.4 C++).

Your Scope: Source/SURFKINI/UI/
Context Rules: Read .clinerules/surfkini.md

Task Objectives:
1. Scaffold SpeedMeterWidget.h and SpeedMeterWidget.cpp to display real-time horizontal velocity (u/s or ups), surf state (Grounded/Airborne/Surfing), and acceleration vectors.
2. Scaffold SURFKINIHud.h and SURFKINIHud.cpp to render crosshairs and velocity overlay on HUD.

Do not edit files outside Source/SURFKINI/UI/.
```
