class_name StrafesCalculator
extends RefCounted

# Strafe Efficiency & Sync Calculation Engine
# Source: Surf/Bhop Community Metrics (Clean-Room GDScript Port)

static func calculate_strafe_efficiency(current_vel: Vector3, wish_dir: Vector3, delta_yaw: float) -> Dictionary:
	var move_speed: float = current_vel.length()
	if move_speed < 10.0:
		return {"sync": 100.0, "gain": 0.0}
		
	var angle_to_vel: float = current_vel.normalized().dot(wish_dir)
	var is_correct_side: bool = (delta_yaw > 0.0 and wish_dir.x > 0.0) or (delta_yaw < 0.0 and wish_dir.x < 0.0)
	
	var sync_pct: float = clampf(angle_to_vel * 100.0, 0.0, 100.0) if is_correct_side else 0.0
	var vel_gain: float = current_vel.dot(wish_dir)
	
	return {
		"sync": sync_pct,
		"gain": vel_gain,
		"is_optimal": sync_pct > 75.0
	}
