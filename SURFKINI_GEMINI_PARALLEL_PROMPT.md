# SURFKINI — Parallel Gemini CLI Prompts & Cross-Discipline Board

> **Cardinal Rule**: Don't derive physics/netcode/timer math from scratch. Find a real, named, published open-source implementation and port its approach — clean-room re-typed into SURFKINI's C++ architecture with `// Source: <repo>, <file>` attribution comments.

---

## 1. Governance & Lane Ownership Matrix

| Agent ID | Lane Role | Target Directory Scope | Branch | Primary Reference |
| :--- | :--- | :--- | :--- | :--- |
| **Zeta** | World & Ramp Geometry | `Source/SURFKINI/World/` | `gemini/world-leveldesign` | `momentum-mod/game` & Lyra Starter Game |
| **Eta** | Progression & Timer Meta | `Source/SURFKINI/Meta/` | `gemini/progression-meta` | `SurfTimer/CSGO-SurfTimer` |
| **Theta** | QA, Testing & CI/CD | `Source/SURFKINITests/`, `.github/workflows/` | `gemini/qa-cicd` | `game-ci/cli` & `unrealcontainers` |
| **Iota** | VFX, Water & Materials | `Source/SURFKINI/VFX/` | `gemini/vfx-water` | GPU Gems & UE5 Water Plugin |
| **Kappa** | Accessibility & L10n | `Source/SURFKINI/Accessibility/` | `gemini/accessibility-l10n` | Game Accessibility Guidelines |
| **Lambda** | Anti-Cheat Validation | `Source/SURFKINI/Net/Validation/` | `gemini/anticheat-validation` | Gabriel Gambetta Netcode |
| **Mu** | Docs & Board Rollup | `README.md`, `CONTRIBUTING.md` | `gemini/docs-board` | Workspace Synthesis |

---

## 2. Per-Agent STATUS.md Protocol

Each agent maintains a tiny isolated `STATUS.md` inside its target scope directory (e.g. `Source/SURFKINI/World/STATUS.md`) to prevent git merge conflicts across parallel worktrees.
Agent Mu sweeps all `STATUS.md` files at the end of each iteration cycle to update master progress reports.
