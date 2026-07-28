# SURFKINI — AI Agent Operating Mandate & Code Adaptation Rules

> **MANDATORY RULE FOR ALL AI AGENTS**:  
> **NEVER WRITE CUSTOM CODE OR INVENT NEW ALGORITHMS FROM SCRATCH.**  
> Every single feature, physics equation, networking structure, weapon recoil pattern, or UI component MUST be directly copied and adapted from established, published open-source repositories and verified math models on GitHub or Valve SDK source releases.

---

## 1. Primary Source Attribution Table

All code modifications across modules MUST explicitly reference one of the following authoritative sources in top-of-file header comments:

| Feature / Domain | Required Open-Source Reference Baseline | Repository / Source URL |
| :--- | :--- | :--- |
| **Air-strafing & Surf Physics** | Valve Source SDK 2013 `gamemovement.cpp` (`PM_AirAccelerate`, `PM_ClipVelocity`) | `ValveSoftware/source-sdk-2013` |
| **Godot/UE Clean Math Port** | Godot 4 Source Engine Movement (MIT) | `EricXu1728/Godot4SourceEngineMovement` |
| **Client-Side Prediction & Rewind** | Fast-Paced Multiplayer Architecture | Gabriel Gambetta (gabrielgambetta.com/client-side-prediction.html) |
| **UDP Socket Transport** | ENet Reliable UDP Networking Library | `lsquic` / `lsd/enet` |
| **Weapon Recoil & Armor Math** | CS:GO Weapon Mechanics Tables & Armor Degradation Formula ($70/30$ ratio) | Valve CS:GO VPK dumps & Counter-Strike wiki specs |
| **Mass Entity Crowd Surf** | UE5 MassEntity & MassMovement Engine Sample | `EpicGames/UnrealEngine` (Engine/Source/Runtime/MassEntity) |
| **Surf HUD & Speedometer** | CS:GO SurfTimer / Momentum Mod HUD | `momentum-mod/game` |

---

## 2. strict Implementation Guidelines

1. **Direct Translation Only**:
   - When porting `PM_ClipVelocity` or `PM_AirAccelerate`, copy the exact math logic variable for variable (`wishdir`, `wishspeed`, `currentspeed`, `addspeed`, `accel`, `overbounce = 1.001f`).
   - Do NOT introduce custom drag or dampening multipliers that depart from the Source Engine standard.

2. **No Invented APIs**:
   - Use standard Unreal Engine 5 C++ classes (`UPawnMovementComponent`, `AAIController`, `UUserWidget`, `UCanvasPanel`).
   - Do NOT invent fake macros or non-standard macros (e.g. use `DOREPLIFETIME` for Net replication).

3. **Verification Before Merging**:
   - Every file change MUST pass compilation via `D:\GMS\UE_5.8\Engine\Build\BatchFiles\Build.bat SURFKINIEditor Win64 Development D:\CODING\SURFKINI\SURFKINI\SURFKINI.uproject`.
