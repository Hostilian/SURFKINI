# SURFKINI — Baseline Warnings Audit Report

- **Date**: 2026-07-28 22:12 CEST
- **Commit Hash**: `e20dd4316200bebade65d6ce28addc0a682b779b`
- **Compiler**: MSVC 14.44.35228

---

## Active Warnings Log

1. **`warning CS0618: 'EngineIncludeOrderVersion.Unreal5_4' is obsolete`**
   - **Resolution**: Fixed in `SURFKINI.Target.cs` and `SURFKINIEditor.Target.cs` by upgrading `IncludeOrderVersion = EngineIncludeOrderVersion.Latest;`.

2. **`LF will be replaced by CRLF`**
   - **Resolution**: Non-critical Windows line-ending normalization warning. All `.cpp` and `.h` files are saved with standard Windows CRLF or clean UTF-8 line endings.

3. **Shadowed Variable Warning in `USurfMovementComponent`**
   - **Resolution**: Fixed by removing duplicate member declaration of `Velocity` in `SurfMovementComponent.h` to inherit `UMovementComponent::Velocity` directly.
