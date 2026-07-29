class_name TeleportDetector
extends RefCounted

static func is_teleport_illegal(from_pos: Vector3, to_pos: Vector3, is_checkpoint_teleport: bool = false) -> bool:
	if is_checkpoint_teleport:
		return false # Legitimate zone teleport
		
	var dist_sqr: float = from_pos.distance_squared_to(to_pos)
	return dist_sqr > 1000000.0 # 1000 units max frame delta
