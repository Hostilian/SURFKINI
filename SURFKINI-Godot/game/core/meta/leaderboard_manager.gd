class_name LeaderboardManager
extends Node

# Local Top-N Leaderboard & Split Tracker

var top_runs: Array = []

func submit_run(player_name: String, map_name: String, time_ms: int) -> bool:
	top_runs.append({
		"name": player_name,
		"map": map_name,
		"time_ms": time_ms,
		"timestamp": Time.get_unix_time_from_system()
	})
	top_runs.sort_custom(func(a, b): return a["time_ms"] < b["time_ms"])
	if top_runs.size() > 10:
		top_runs.resize(10)
	return true
