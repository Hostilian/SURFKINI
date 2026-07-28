# SURFKINI — Baseline Performance & Profiling Report

- **Date**: 2026-07-28 22:12 CEST
- **Target Frame Rate**: 144 FPS Competitive / 60 FPS Minimum
- **Target Resolution**: 1080p / 1440p

---

## Subsystem Performance Profiles

| Subsystem | CPU Target | GPU Target | Memory / GC Overhead | Strategy |
| :--- | :--- | :--- | :--- | :--- |
| **Surf Physics** | $< 1.5\text{ms}$ | N/A | Zero GC allocation | 60Hz fixed tick accumulator in `USurfMovementComponent` |
| **Hitscan & Weapons** | $< 0.5\text{ms}$ | $< 0.2\text{ms}$ | Zero GC allocation | `TSurfObjectPool` recycling line traces & impact decals |
| **Net Rewind** | $< 1.0\text{ms}$ | N/A | Lock-free ring buffer | 1000ms player transform history buffer in `LagCompensator` |
| **Mass AI Crowd** | $< 2.0\text{ms}$ | N/A | SIMD batch transforms | 60Hz near ($< 2000\text{u}$), 15Hz far ($> 2000\text{u}$) LOD culling |
| **UI Speedometer** | $< 0.3\text{ms}$ | $< 0.1\text{ms}$ | Low UMG draw cost | Direct BlueprintPure speed binding in `USpeedMeterWidget` |
