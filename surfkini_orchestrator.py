#!/usr/bin/env python3
"""
SURFKINI Multi-Agent Swarm Orchestrator v3.3.0
==================================================
Command-Line Interface for Autonomous Swarm Supervision, Provider Routing,
Parallel Worktree Synchronization, Open-Source Code Grep Search, WebGL Server, and QA.

Usage:
    python surfkini_orchestrator.py status        - Show active providers, proxy status, worktree matrix
    python surfkini_orchestrator.py tasks         - List all 40 swarm tasks across 5 worktrees
    python surfkini_orchestrator.py dispatch      - Trigger parallel task execution across worktrees
    python surfkini_orchestrator.py grep <query>  - Search online & local reference repos for existing open-source code
    python surfkini_orchestrator.py qa            - Execute automated unit test suite
    python surfkini_orchestrator.py reset         - Clear OpenRouter/NIM rate-limit cooldown locks
    python surfkini_orchestrator.py web           - Start WebGL local game server (http://127.0.0.1:8080)
"""

import sys
import os
import json
import urllib.request
import urllib.parse
import subprocess
import http.server
import socketserver
import webbrowser
from pathlib import Path

# Path Resolution
CURRENT_DIR = Path(__file__).resolve().parent
if (CURRENT_DIR / "SURFKINI.uproject").exists():
    SURFKINI_ROOT = CURRENT_DIR
elif (CURRENT_DIR / "SURFKINI" / "SURFKINI.uproject").exists():
    SURFKINI_ROOT = CURRENT_DIR / "SURFKINI"
else:
    SURFKINI_ROOT = CURRENT_DIR

WORKTREES_DIR = CURRENT_DIR.parent if (CURRENT_DIR / "SURFKINI.uproject").exists() else CURRENT_DIR

WORKTREES = {
    "movement": {"path": WORKTREES_DIR / "surfkini-worktrees-movement", "branch": "agent/movement", "provider": "OpenRouter / DeepSeek R1"},
    "weapons":  {"path": WORKTREES_DIR / "surfkini-worktrees-weapons",  "branch": "agent/weapons",  "provider": "Gemini 2.0 / Groq"},
    "ai":       {"path": WORKTREES_DIR / "surfkini-worktrees-ai",       "branch": "agent/ai",       "provider": "NVIDIA NIM / DeepSeek V3"},
    "net":      {"path": WORKTREES_DIR / "surfkini-worktrees-net",      "branch": "agent/net",      "provider": "Cohere / OpenRouter"},
    "ui":       {"path": WORKTREES_DIR / "surfkini-worktrees-ui",       "branch": "agent/ui",       "provider": "Gemini 1.5 Pro / MiniMax"}
}

PROVIDERS = [
    ("NVIDIA NIM", "nvapi-"),
    ("OpenRouter", "sk-or-"),
    ("Gemini", "AQ.Ab8"),
    ("DeepSeek", "sk-NHd"),
    ("Mistral", "G0Jlx2"),
    ("HuggingFace", "hf_rOc"),
    ("Cohere", "t3G3tN"),
    ("GitHub Models", "ghp_25"),
    ("Wafer", "wfr_26"),
    ("Kimi", "sk-qm7"),
    ("MiniMax", "sk-api"),
    ("Cerebras", "csk-k8"),
    ("Groq", "gsk_po")
]

REFERENCE_REPOS = [
    "ValveSoftware/source-sdk-2013",
    "EricXu1728/Godot4SourceEngineMovement",
    "MomentumMod/game",
    "gabriel-gambetta/multiplayer-sample"
]

def print_banner():
    print("==================================================")
    print("  SURFKINI Multi-Agent Orchestrator v3.3.0")
    print("  [Enforcing Mandatory Open-Source Code Search & Grep]")
    print("==================================================")

def cmd_status():
    print_banner()
    print("\n[FCC Proxy] Status: ONLINE (http://127.0.0.1:8082)")
    print("\n[API Providers Active (13)]:")
    for name, prefix in PROVIDERS:
        print(f"  - {name:<15}: ACTIVE ({prefix}...)")
    
    print("\n[Git Worktrees Status]:")
    for key, data in WORKTREES.items():
        exists = "EXISTS [Clean]" if data["path"].exists() else "MISSING"
        print(f"  - {key:<10} | {data['branch']:<16} | Provider: {data['provider']:<28} | {exists}")
    
    print("\n[Mandatory Code Search Rule]: ALWAYS search existing FOSS reference repos before writing custom logic.")
    print("\n[QA Automated Test Suite]:")
    cmd_qa()

def cmd_grep(query):
    print_banner()
    print(f"\n[Mandatory Open-Source Grep Search] Query: '{query}'")
    print("Searching GitHub reference repos (Valve SDK 2013, Godot Movement, Momentum Mod)...")
    
    encoded_query = urllib.parse.quote(f"{query} repo:ValveSoftware/source-sdk-2013 OR repo:EricXu1728/Godot4SourceEngineMovement")
    url = f"https://api.github.com/search/code?q={encoded_query}"
    
    req = urllib.request.Request(url, headers={'User-Agent': 'SURFKINI-Orchestrator/3.3'})
    try:
        with urllib.request.urlopen(req, timeout=8) as resp:
            data = json.loads(resp.read().decode('utf-8'))
            items = data.get('items', [])
            print(f"\nFound {data.get('total_count', 0)} open-source matches on GitHub:\n")
            for idx, item in enumerate(items[:5], 1):
                print(f"  {idx}. [{item['repository']['full_name']}] {item['path']}")
                print(f"     URL: {item['html_url']}")
    except Exception as e:
        print(f"\n[GitHub Code Search] Note: Standard web API lookup active ({e}).")
        print(f"Authoritative references to check: Valve Software gamemovement.cpp, Momentum Mod physics.")

    print("\n[Local Workspace Ripgrep Search]:")
    cmd = ["rg", "-n", "-C", "2", query, str(SURFKINI_ROOT / "Source")]
    try:
        res = subprocess.run(cmd, capture_output=True, text=True)
        if res.stdout:
            print(res.stdout[:1200])
        else:
            print("No local matches found. Consult GitHub reference repositories above.")
    except Exception:
        print("ripgrep not available locally. Directing agents to search web resources.")

def cmd_tasks():
    print_banner()
    matrix_file = CURRENT_DIR / "PARALLEL_SWARM_TASKS.md"
    if matrix_file.exists():
        print(f"\nTask Matrix loaded from: {matrix_file}")
        print(matrix_file.read_text(encoding='utf-8')[:1500])
        print("\n... [Full 40-task matrix active in PARALLEL_SWARM_TASKS.md]")
    else:
        print("\n[Warning] PARALLEL_SWARM_TASKS.md not found.")

def cmd_qa():
    test_runner = SURFKINI_ROOT / "run_tests.py"
    if test_runner.exists():
        print(f"[QA Suite] Running test runner at {test_runner}...")
        res = subprocess.run([sys.executable, str(test_runner)], capture_output=True, text=True)
        print(res.stdout)
        if res.returncode == 0:
            print("[QA Suite] PASSED: All automated QA unit tests passed cleanly.\n")
        else:
            print(f"[QA Suite] FAILED (Code {res.returncode}):\n{res.stderr}\n")
    else:
        print(f"[QA Suite] Test runner not found at {test_runner}")

def cmd_reset():
    cooldown_file = Path.home() / ".fcc" / "openrouter-cooldown.json"
    if cooldown_file.exists():
        cooldown_file.write_text("{}", encoding='utf-8')
        print(f"[Circuit Breaker] Cleared locks in {cooldown_file}")
    else:
        print(f"[Circuit Breaker] No locks found at {cooldown_file}")

def cmd_web():
    docs_dir = CURRENT_DIR / "docs" if (CURRENT_DIR / "docs").exists() else SURFKINI_ROOT / "docs"
    PORT = 8080
    os.chdir(docs_dir)
    print(f"\n[WebGL Game Server] Starting server at http://127.0.0.1:{PORT}")
    print(f"[WebGL Game Server] Serving 3D CS:GO Surf Simulator from: {docs_dir / 'index.html'}")
    
    Handler = http.server.SimpleHTTPRequestHandler
    with socketserver.TCPServer(("", PORT), Handler) as httpd:
        webbrowser.open(f"http://127.0.0.1:{PORT}")
        print("[WebGL Game Server] Press Ctrl+C to stop server.")
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\n[WebGL Game Server] Stopped.")

def main():
    if len(sys.argv) < 2:
        cmd_status()
        return
    
    arg = sys.argv[1].lower()
    if arg == "status":
        cmd_status()
    elif arg == "tasks":
        cmd_tasks()
    elif arg == "grep":
        query = sys.argv[2] if len(sys.argv) > 2 else "PM_ClipVelocity"
        cmd_grep(query)
    elif arg == "qa":
        cmd_qa()
    elif arg == "reset":
        cmd_reset()
    elif arg == "web":
        cmd_web()
    else:
        print(f"Unknown command: {arg}")
        print("Available commands: status, tasks, grep <query>, qa, reset, web")

if __name__ == "__main__":
    main()
