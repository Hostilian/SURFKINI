---
name: surfkini-parallel-agent-dispatch
description: Parallel Multi-Agent Dispatch Skill for SURFKINI Unreal Engine 5 C++ project with worktree isolation and FCC Claude CLI.
---

# SURFKINI Parallel Agent Dispatch

## Overview
SURFKINI uses `fcc-claude` (Claude Code CLI via local FCC server) to run specialized sub-agents in parallel using Git worktrees.

## Agent Role Assignment & Scopes

| Agent Name | Worktree Branch | Scoped Directory | Responsibility |
|------------|-----------------|------------------|----------------|
| `movement-physics` | `agent/movement` | `Source/SURFKINI/Movement/` | Surf physics, ClipVelocity, ground/air accel, replication |
| `weapons-combat` | `agent/weapons` | `Source/SURFKINI/Weapons/` | Weapon base, hitscan, projectiles, damage, lag compensation |
| `ai-mass-entity` | `agent/ai` | `Source/SURFKINI/AI/` | Mass Entity processors, Behavior Trees, RL Macro-agents |
| `multiplayer-net` | `agent/net` | `Source/SURFKINI/Net/` | Nakama integration, ENet server authority, client prediction |
| `ui-hud` | `agent/ui` | `Source/SURFKINI/UI/` | Speed meter, HUD, kill feed, main menu |

## Dispatch Execution Pattern
```powershell
# Spawn parallel agents in isolated worktrees
python surfkini_orchestrator.py --mode sidecar --tasks movement,weapons,ai
```

## Rules of Isolation
1. Never edit files outside your assigned directory scope.
2. Commit changes to your worktree branch (`agent/<scope>`).
3. Maintain status in `.agents/state/agent-status.md`.
4. Never force-push or reset `main`.
