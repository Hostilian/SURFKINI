# SURFKINI — Godot 4.7.1 Cross-Platform Feasibility Pivot Architecture

> **Lead Architect**: Autonomous Gemini Lead Game Director & Multi-Agent Architect  
> **Target Engine**: Godot 4.7.1 Standard (Typed GDScript Baseline)  
> **Archived Prototype**: Unreal Engine 5.8 C++ (`unreal-prototype-2026-07` tag preserved)  
> **Target Profiles**: Full Native (Windows/Linux), Mobile Native (Android/iOS), Web Lite (WebAssembly / WebGL 2 Compatibility)

---

## 🏛️ 1. Architecture Overview & Engine Decision

The engine decision has been updated based on the hard requirements for:
1. **Direct WebAssembly / Browser Export**: Zero GPU streaming cost, single shared codebase.
2. **100% Free & Open-Source Software (FOSS)**: MIT-licensed engine with zero commercial royalties or mandatory API billing.
3. **Multi-Platform Scalability**: Native Desktop (Windows/Linux ENet UDP), Mobile (Android NDK/iOS Metal), and Browser (WebRTC DataChannel / WebSockets).

---

## 📦 2. Product Profiles & Platform Scope

| Profile | Platforms | Graphics API | Target Experience | Networking |
| :--- | :--- | :--- | :--- | :--- |
| **Full Native** | Windows x64, Linux x64 | Forward+ / Compatibility | 8–16 player combat, full VFX, high refresh rate | ENet / UDP |
| **Mobile Native**| Android, iOS | Mobile / Compatibility | Touch/gyro controls, reduced VFX, 4–8 players | ENet / UDP |
| **Web Lite** | Desktop/Mobile Browsers | WebGL 2 Compatibility | Surf lab, time trials, ghosts, 2–4 players | WebRTC / WebSockets |

---

## 🗺️ 3. 9-Phase Master Development Roadmap

- **Phase 0 — Engine Feasibility Gate**: Godot 4.7.1 project creation, exports for Windows/Linux/Android/Web, typed GDScript `SurfController`.
- **Phase 1 — Autonomous Development Factory**: 18 specialized agent roles, SQLite task DB, Ollama/OpenCode/Gemini local adapters.
- **Phase 2 — Movement Laboratory**: Flat acceleration, 30°/45°/60° ramps, ramp transfers, coyote time, and subtick buffering.
- **Phase 3 — Shooting Sandbox**: Precision automatic rifle & spread weapon, server-authoritative damage, original recoil tables.
- **Phase 4 — Multiplayer Movement**: ENet UDP transport, 1000ms rewind buffer, client prediction replay, server authority.
- **Phase 5 — Web Multiplayer Feasibility**: WebRTC DataChannel for browser gameplay, WebSocket for lobbies/leaderboards.
- **Phase 6 — First Complete Vertical Slice**: Surf Combat Trial mode (1 tutorial map, 1 competitive map, 2 weapons, 4–8 players).
- **Phase 7 — Mobile Adaptation**: Touch virtual joystick, gyro aiming, safe-area layout, Android APK & iOS Xcode build.
- **Phase 8 — Content, Bots & Progression**: State-machine surf bots, time-trial medals, replay ghosts, CC0 map assets.
- **Phase 9 — Public Hardening & Release**: Packaging, itch.io Web deployment, asset licenses verification, performance audits.
