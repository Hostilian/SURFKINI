#!/usr/bin/env python3
r"""
SURFKINI AI Multi-Agent Orchestrator v1.0.0
===========================================

Supervises parallel agent execution, git worktrees, and task dispatch for
Unreal Engine 5 SURFKINI development using local FCC server proxy (http://127.0.0.1:8082).
"""

import os
import sys
import json
import time
import subprocess
import urllib.request
from pathlib import Path

VERSION = "1.0.0"
PROJECT_ROOT = Path(__file__).parent.resolve()
FCC_HEALTH_URL = "http://127.0.0.1:8082/health"

AGENT_SCOPES = {
    "movement": {
        "branch": "agent/movement",
        "path": "Source/SURFKINI/Movement",
        "desc": "Surf movement physics, ClipVelocity, air accel, replication"
    },
    "weapons": {
        "branch": "agent/weapons",
        "path": "Source/SURFKINI/Weapons",
        "desc": "Weapon base, hitscan, projectiles, lag compensation"
    },
    "ai": {
        "branch": "agent/ai",
        "path": "Source/SURFKINI/AI",
        "desc": "Mass Entity surf processors, Behavior Trees, Macro RL agents"
    },
    "net": {
        "branch": "agent/net",
        "path": "Source/SURFKINI/Net",
        "desc": "ENet server authority, client prediction, reconciliation"
    },
    "ui": {
        "branch": "agent/ui",
        "path": "Source/SURFKINI/UI",
        "desc": "HUD, speed meter, kill feed, scoreboard"
    }
}

def check_fcc_health() -> bool:
    try:
        req = urllib.request.Request(FCC_HEALTH_URL)
        with urllib.request.urlopen(req, timeout=3) as resp:
            return resp.status == 200
    except Exception:
        return False

def init_worktree(scope: str) -> Path:
    if scope not in AGENT_SCOPES:
        raise ValueError(f"Unknown scope: {scope}")

    info = AGENT_SCOPES[scope]
    worktree_dir = PROJECT_ROOT.parent / f"surfkini-worktrees-{scope}"
    branch = info["branch"]

    print(f"[Orchestrator] Initializing worktree for '{scope}' at {worktree_dir}...")
    
    # Check if branch exists
    res = subprocess.run(["git", "branch", "--list", branch], cwd=PROJECT_ROOT, capture_output=True, text=True)
    if not res.stdout.strip():
        subprocess.run(["git", "branch", branch], cwd=PROJECT_ROOT, check=True)

    if not worktree_dir.exists():
        subprocess.run(["git", "worktree", "add", str(worktree_dir), branch], cwd=PROJECT_ROOT, check=True)

    return worktree_dir

def main():
    print(f"==================================================")
    print(f"  SURFKINI Multi-Agent Orchestrator v{VERSION}")
    print(f"==================================================")

    healthy = check_fcc_health()
    if healthy:
        print("[FCC Status] ONLINE (http://127.0.0.1:8082)")
    else:
        print("[FCC Status] OFFLINE - Run 'fcc-server.bat' first")

    if len(sys.argv) > 1 and sys.argv[1] == "worktrees":
        for scope in AGENT_SCOPES:
            try:
                wt = init_worktree(scope)
                print(f"  - {scope}: {wt}")
            except Exception as e:
                print(f"  - {scope} failed: {e}")
    else:
        print("\nAvailable commands:")
        print("  python surfkini_orchestrator.py worktrees   # Set up isolated worktrees for all agents")

if __name__ == "__main__":
    main()
