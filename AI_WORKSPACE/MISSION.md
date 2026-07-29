# SURFKINI — AI WORKSPACE PERSISTENT MISSION CONTRACT

**Project**: SURFKINI  
**Engine**: Unreal Engine 5.8 C++  
**Target Platforms**: Windows & Linux  
**Repository**: `Hostilian/SURFKINI`  
**Workspace Path**: `d:\CODING\SURFKINI\SURFKINI`  

---

## 🎯 Primary Goal
Transform SURFKINI into an original, highly competitive, multiplayer momentum FPS combining CS/Source surf physics, Titanfall parkour wall-running & mantling, Gears of War high-speed wall collision damage ($Damage = k \cdot (v_{\text{impact}} - v_{\text{threshold}})^2$), dual first/third-person cameras, 128 tickrate dedicated servers, in-game runtime level builder, Steam Workshop community maps, modular loadouts/gear systems, and Tier 1 data mods.

---

## 🔒 Mandatory Operating Rules
1. **Search-First Gate Protocol**: Every feature must execute 3-pass open-source code research (`python tools/research_gate.py`) and licence classification (`tools/licence_classifier.py`).
2. **Clean-Room Compliance**: No proprietary, stolen, or decompiled code. Attribution preserved in `THIRD_PARTY.md` and `ASSET_MANIFEST.csv`.
3. **Multiplayer Authority**: Server owns player transforms, velocity, health, armor, fire validation, and 1000ms lag compensation rewind (`ULagCompensator`).
4. **Persistent Memory Reload**: Read state files from `AI_WORKSPACE/` at session startup.
