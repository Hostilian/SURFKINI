# SURFKINI — Project Constitution & Engineering Policy

> **Status**: APPROVED & ACTIVE  
> **Target Scope**: Multi-Platform Momentum Surf FPS Engine (Unreal C++ & Godot 4.7.1 FOSS)  
> **Repository**: https://github.com/Hostilian/SURFKINI

---

## 1. Core Directives

1. **Original IP Mandate**: SURFKINI is an original momentum-based surf FPS game. No proprietary asset names, characters, weapon models, sound files, or textures from third-party games may be included.
2. **Clean-Room Engineering**: All Source engine movement math, velocity clipping algorithms, and client prediction mechanisms must be clean-room implemented with explicit source attributions (`// Source: <repo>/<file>`).
3. **Licensing Policy**: 100% Free & Open-Source Software (FOSS). Permitted licenses: MIT, BSD-3-Clause, Apache-2.0, CC0. No GPL-3.0 or proprietary code.
4. **Primary Release Targets**: Windows (x86_64) and Linux (x86_64).
5. **Secondary Targets**: Android (ARM64 Vulkan/GLES), iOS (Metal export), WebAssembly (GL Compatibility 60Hz).

---

## 2. Architectural Conventions

### 2.1 Code Structure & Naming Rules
- GDScript files must use `snake_case.gd`. Classes must use `PascalCase` with `class_name`.
- C++ headers must use `PascalCase.h` prefixed with `Surf` or `ASurf` for AActor subclasses.
- All public functions must specify return types and parameter types (`typed GDScript`).

### 2.2 Versioning & Branch Discipline
- Semantic Versioning: `MAJOR.MINOR.PATCH` (e.g. `v0.1.0-alpha`).
- Branch naming: `feature/<scope>-<description>`, `agent/<scope>`, `fix/<issue-id>`.
- Commit messages: Follow Conventional Commits (`feat(movement): ...`, `fix(net): ...`, `docs(gov): ...`).

---

## 3. Security, Quality & Release Gates

1. **Automated Testing**: Unit tests must pass (`python run_tests.py`) before merging any branch into `main`.
2. **Anti-Cheat Validation**: Server-authoritative movement validation must enforce strict velocity caps and slope angle bounds.
3. **Zero Secrets**: API keys, credentials, or access tokens are strictly prohibited in git commits.
4. **Release Gate**: No public release binary may be built without passing CI regression suites and security scans.
