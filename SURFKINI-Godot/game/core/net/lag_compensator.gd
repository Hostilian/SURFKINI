class_name LagCompensator
extends RefCounted

# Client Lag Compensation Target Position Rewind Engine

static func rewind_target_position(history: Array, target_time_ms: int) -> Vector3:
	if history.is_empty():
		return Vector3.ZERO
		
	for record in history:
		if record.has("time_ms") and record["time_ms"] <= target_time_ms:
			return record["position"]
			
	return history[0]["position"]
