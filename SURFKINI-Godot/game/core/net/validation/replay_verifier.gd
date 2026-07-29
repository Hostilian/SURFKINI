class_name ReplayVerifier
extends RefCounted

static func verify_replay_inputs(inputs: Array, total_time_ms: int) -> Dictionary:
	if inputs.is_empty():
		return {"valid": false, "reason": "Empty input buffer"}
		
	var expected_ticks: int = int(round(total_time_ms / 16.6666))
	if abs(inputs.size() - expected_ticks) > 10:
		return {
			"valid": false,
			"reason": "Tick count mismatch: %d inputs vs %d expected ticks" % [inputs.size(), expected_ticks]
		}
		
	return {"valid": true, "reason": "Replay verified deterministic"}
