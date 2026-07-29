# SURFKINI — MISTAKE & BUG PREVENTION LEDGER

- **MISTAKE-001**: Missing Three.js library CDN script tag in `docs/index.html`.
  - **Symptom**: Black screen when opening WebGL client at `http://127.0.0.1:8080/`.
  - **Root Cause**: `THREE` was undefined, crashing JavaScript initialization.
  - **Fix**: Added `<script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js"></script>` to `<head>` and auto-started `animate()` loop in `init()`.

- **MISTAKE-002**: `ConstructorHelpers::FObjectFinder` used inside `SurfTestMapBuilder.cpp` during dynamic actor runtime spawn.
  - **Symptom**: Engine fatal crash: `FObjectFinders can't be used outside of constructors to find /Engine/BasicShapes/Cube.Cube`.
  - **Root Cause**: `FObjectFinder` is only permitted during startup CDO load.
  - **Fix**: Replaced with `LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"))` in `BeginPlay()`.
