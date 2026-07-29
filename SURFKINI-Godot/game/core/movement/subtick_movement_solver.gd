class_name SubtickMovementSolver
extends RefCounted

# 1000Hz Sub-Stepping Movement Integrator

static func integrate_subticks(pos: Vector3, vel: Vector3, wish_dir: Vector3, delta_time: float, steps: int = 10) -> Dictionary:
	var dt_step: float = delta_time / float(max(steps, 1))
	var current_pos: Vector3 = pos
	var current_vel: Vector3 = vel
	
	for i in range(steps):
		current_vel += wish_dir * 10.0 * dt_step
		current_pos += current_vel * dt_step
		
	return {
		"position": current_pos,
		"velocity": current_vel
	}
