# SURFKINI — Master Parallel Multi-Agent Upgrade Checklist

> **Role**: Lead Game Director & Multi-Agent Architect  
> **Target Engine**: Unreal Engine 5.8 (C++)  
> **Mandate**: **ZERO CODE FROM SCRATCH.** All features, shaders, mechanics, audio, and UI components are directly adapted from established, open-source GitHub repositories with explicit citations.

---

## 1. Agent Alpha (Graphics & Rendering Agent)
**Branch Scope**: `surfkini-worktrees-movement` / `Graphics/`  
**Open-Source References**: `EpicGames/UnrealEngine` & `Unity-Technologies/Graphics` PostProcessing Stack  

- [ ] **Task Alpha-1**: Port camera velocity tilt & spring arm roll formula ($\theta_{\text{roll}} = \text{Clamp}(\vec{v} \cdot \vec{r}_{\text{right}} \times 0.005^\circ, -5^\circ, 5^\circ)$) from Source SDK `in_camera.cpp`.
- [ ] **Task Alpha-2**: Create `USurfPostProcessComponent` for dynamic speed lines post-processing effect based on player speed ratio ($V_{\text{speed}} / 3500\text{ u/s}$).
- [ ] **Task Alpha-3**: Adapt bullet impact particle effect pool from Unreal Engine Sample Project (`Engine/Content/VFX`).

---

## 2. Agent Beta (Core Gameplay & Physics Agent)
**Branch Scope**: `surfkini-worktrees-weapons` / `Movement/` & `Weapons/`  
**Open-Source References**: `ValveSoftware/source-sdk-2013` (`gamemovement.cpp`) & CS:GO Recoil Tables  

- [x] **Task Beta-1**: Port clean-room `ClipVelocity` (overbounce $= 1.001f$, $\cos 45^\circ = 0.707f$ ramp threshold) from Valve Source SDK 2013.
- [ ] **Task Beta-2**: Port Subtick Jump Buffer ($8\text{ms}$ window) and Coyote Time ($100\text{ms}$ grace window).
- [ ] **Task Beta-3**: Implement CS:GO AK-47 30-bullet recoil spray pattern with decay recovery curve.
- [ ] **Task Beta-4**: Implement Kevlar $70/30$ armor damage deduction math ($70\%$ health, $30\%$ armor).

---

## 3. Agent Gamma (UI, UX & Interface Agent)
**Branch Scope**: `surfkini-worktrees-ui` / `UI/`  
**Open-Source References**: `momentum-mod/game` & `SurfTimer/CSGO-SurfTimer`  

- [x] **Task Gamma-1**: Create `USpeedMeterWidget` displaying real-time units per second ($\text{u/s}$).
- [ ] **Task Gamma-2**: Color-code speedometer tiers (Blue $< 500$, Yellow $500-1500$, Green $> 1500\text{ u/s}$).
- [ ] **Task Gamma-3**: Dynamic canvas crosshair rendering scaling with velocity magnitude and weapon spread angle.
- [ ] **Task Gamma-4**: Killfeed notification stack displaying headshot badges and weapon icons.

---

## 4. Agent Delta (Audio & Sound System Agent)
**Branch Scope**: `surfkini-worktrees-net` / `Audio/`  
**Open-Source References**: `ValveSoftware/source-sdk-2013` (`soundpanning.cpp`)  

- [ ] **Task Delta-1**: Create `USurfAudioComponent` for dynamic surf wind shear volume attenuation ($\text{Volume} = \text{Clamp}(V_{\text{speed}} / 2500.0f, 0.0f, 1.0f)$).
- [ ] **Task Delta-2**: Integrate footstep and ramp impact sound triggers.
- [ ] **Task Delta-3**: Add 3D spatial audio positioning for weapon gunfire.

---

## 5. Agent Epsilon (Performance & Optimization Agent)
**Branch Scope**: `surfkini-worktrees-ai` / `Performance/` & `AI/`  
**Open-Source References**: `OpenPool/cpp-object-pool` & `EpicGames/UnrealEngine` MassEntity  

- [ ] **Task Epsilon-1**: Implement template-based C++ high-performance `SurfObjectPool` for line trace hit results and decals.
- [ ] **Task Epsilon-2**: Scale `SurfMassProcessor` 60Hz surf entity crowd simulation to 1,000 entities.
- [ ] **Task Epsilon-3**: Implement spatial grid distance culling (60Hz $< 2000\text{ units}$, 15Hz $> 2000\text{ units}$).

---

## 6. Execution & Verification Protocol

Run compilation check after any batch update:
```powershell
cmd.exe /c "D:\GMS\UE_5.8\Engine\Build\BatchFiles\Build.bat SURFKINIEditor Win64 Development D:\CODING\SURFKINI\SURFKINI\SURFKINI.uproject -waitmutex"
```
