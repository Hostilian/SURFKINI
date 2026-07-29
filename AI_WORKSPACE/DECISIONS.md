# SURFKINI — ARCHITECTURAL DECISION RECORDS (ADR)

- **ADR-001**: Use `LoadObject<T>` instead of `ConstructorHelpers::FObjectFinder` for dynamic runtime asset loading to eliminate line 4971 assertion crashes when actors are spawned at runtime during `BeginPlay()`.
- **ADR-002**: Enforce 3-pass research gate (`tools/research_gate.py`) and licence classification (`tools/licence_classifier.py`) prior to implementing any feature module.
- **ADR-003**: Implement server-authoritative kinetic impact damage formula: $Damage = k \cdot (v_{\text{impact}} - v_{\text{threshold}})^2$ with Kevlar 70/30 armor deduction.
- **ADR-004**: Implement dual camera system using `USpringArmComponent` with dynamic over-the-shoulder perspective and 'V' key toggle.
