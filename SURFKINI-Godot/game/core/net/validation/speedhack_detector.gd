class_name SpeedhackDetector
extends RefCounted

# Server-Side Clock & Tick Rate Speedhack Validator

static func is_tick_rate_exploited(server_ticks: int, client_ticks: int, allowed_skew: int = 5) -> bool:
	return abs(client_ticks - server_ticks) > allowed_skew
