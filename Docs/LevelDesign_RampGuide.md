# SURFKINI — Level Design & Ramp Building Guide

> **Author**: Agent Zeta (World & Level Design Specialist)  
> **Source Standards**: `momentum-mod/game` & Valve Developer Community Ramp Conventions

---

## 1. Ramp Geometry Specifications
- **Optimal Ramp Slope**: 45.0° (Min: 40.0°, Max: 75.0°)
- **Segment Curve Division**: 8 to 16 unit segments per curved section to ensure smooth sweep collision without micro-bounce.
- **Ramp Surface Tagging**: Attach `USurfRampTaggingComponent` to all static mesh ramp volumes.

---

## 2. Checkpoint & Trigger Placement
- **Start Zone**: Box volume with `FOnSurfTimerUpdated` trigger.
- **End Zone**: Finish line volume with run validation check.
- **Out of Bounds (OOB)**: Kill/reset volume elevated below ramps to reset player to last valid checkpoint.
