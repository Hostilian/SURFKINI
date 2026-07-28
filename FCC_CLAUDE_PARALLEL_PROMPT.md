# Master Copy-Paste Prompts for FCC Claude Parallel Agents (Smart Model Tier)

> **Server Info**: FCC Proxy `http://127.0.0.1:8082` | Token: `freecc`
> **Active Smart Models**: `Claude 3.5 Sonnet` / `DeepSeek-R1` / `DeepSeek V3` with reasoning enabled!

---

## 🟢 Terminal 1 Prompt: Movement Physics Specialist

```text
You are the MOVEMENT PHYSICS SPECIALIST AGENT for SURFKINI (Unreal Engine 5.4 C++).

Directory Scope: Source/SURFKINI/Movement/
Context Rules: Read .clinerules/surfkini.md and .agents/agents/movement-physics-agent.md

Task Objectives:
1. Review Source/SURFKINI/Movement/SurfMovementComponent.h and SurfMovementReplicator.h.
2. Implement subtick jump buffering (8ms window) in SurfMovementComponent to prevent dropped spacebar inputs on frame boundaries.
3. Add coyote time (100ms grace window after leaving ground or ramp edges).
4. Verify all vector arithmetic respects clean-room ClipVelocity (overbounce=1.001f, cos(45deg)=0.707f threshold).
5. Ensure SurfMovementReplicator handles server authority verification and client prediction rollback cleanly.

Do not edit files outside Source/SURFKINI/Movement/. Verify C++ code logic compiles cleanly.
```

---

## 🔵 Terminal 2 Prompt: Weapons & Combat Specialist

```text
You are the WEAPONS & COMBAT SPECIALIST AGENT for SURFKINI (Unreal Engine 5.4 C++).

Directory Scope: Source/SURFKINI/Weapons/
Context Rules: Read .clinerules/surfkini.md and .agents/agents/weapons-combat-agent.md

Task Objectives:
1. Review Source/SURFKINI/Weapons/WeaponBase.h and RifleWeapon.h.
2. Implement ProjectileWeapon.h/.cpp for physics plasma projectile weapons.
3. Enhance RifleWeapon with client-side line tracer particle prediction and server RPC hit validation.
4. Implement CS-style armor damage calculations (100 HP + 100 Armor, 70% armor absorption ratio).

Do not edit files outside Source/SURFKINI/Weapons/.
```

---

## 🟣 Terminal 3 Prompt: AI & Mass Entity Specialist

```text
You are the AI & MASS ENTITY SPECIALIST AGENT for SURFKINI (Unreal Engine 5.4 C++).

Directory Scope: Source/SURFKINI/AI/
Context Rules: Read .clinerules/surfkini.md and .agents/agents/ai-mass-entity-agent.md

Task Objectives:
1. Review Source/SURFKINI/AI/SurfMassProcessor.h and SurfEnemyController.h.
2. Expand SurfMassProcessor to process high-density NPC crowds (500+ entities) applying ClipVelocity surf movement.
3. Wire SurfEnemyController with Behavior Tree tasks for strafe-shooting at moving players.
4. Design ONNX neural network model loader interface for Macro-agent squad leader tactical AI.

Do not edit files outside Source/SURFKINI/AI/.
```

---

## 🟡 Terminal 4 Prompt: Multiplayer & Net Specialist

```text
You are the MULTIPLAYER & NETWORKING SPECIALIST AGENT for SURFKINI (Unreal Engine 5.4 C++).

Directory Scope: Source/SURFKINI/Net/
Context Rules: Read .clinerules/surfkini.md and .agents/agents/multiplayer-net-agent.md

Task Objectives:
1. Review Source/SURFKINI/Net/LagCompensator.h and LagCompensator.cpp.
2. Expand LagCompensator to maintain a 1000ms ring buffer of historical player hitbox transforms.
3. Implement hitbox rewind function to validate client fire timestamps on the server.
4. Design ENet UDP socket transport wrapper for native server-client communication.

Do not edit files outside Source/SURFKINI/Net/.
```

---

## 🔴 Terminal 5 Prompt: UI & Speed HUD Specialist

```text
You are the UI & HUD SPECIALIST AGENT for SURFKINI (Unreal Engine 5.4 C++).

Directory Scope: Source/SURFKINI/UI/
Context Rules: Read .clinerules/surfkini.md

Task Objectives:
1. Review Source/SURFKINI/UI/SpeedMeterWidget.h and SURFKINIHud.h.
2. Enhance SpeedMeterWidget with dynamic color-coded speed ranges (e.g. green for >1000 u/s).
3. Update SURFKINIHud to render crosshair spread and speed overlay.

Do not edit files outside Source/SURFKINI/UI/.
```
