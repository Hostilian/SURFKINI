class_name MoveValidator
extends RefCounted

const MAX_PERMITTED_VELOCITY: float = 3500.0
const MAX_TELEPORT_DISTANCE_SQR: float = 250000.0 # 500 units per frame max

static func validate_move(prev_pos: Vector3, new_pos: Vector3, velocity: Vector3, delta_time: float) -> Dictionary:
	var speed: float = velocity.length()
	if speed > MAX_PERMITTED_VELOCITY:
		return {
			"valid": false,
			"reason": "Speed violation: %.1f > MAX %.1f" % [speed, MAX_PERMITTED_VELOCITY]
		}
		
	var dist_sqr: float = prev_pos.distance_squared_to(new_pos)
	if dist_sqr > MAX_TELEPORT_DISTANCE_SQR:
		return {
			"valid": false,
			"reason": "Teleport anomaly detected"
		}
		
	return {"valid": true, "reason": "OK"}
