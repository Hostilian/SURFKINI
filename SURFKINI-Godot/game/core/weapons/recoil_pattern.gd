class_name RecoilPattern
extends RefCounted

# Procedural Recoil Pattern & Decay Recovery

static func calculate_recoil_offset(shot_count: int, max_recoil_pitch: float = 0.05, max_recoil_yaw: float = 0.02) -> Vector2:
	var pitch: float = minf(shot_count * 0.005, max_recoil_pitch)
	var yaw: float = sin(shot_count * 0.8) * max_recoil_yaw
	return Vector2(yaw, pitch)

static func decay_recoil(current_recoil: Vector2, decay_rate: float, delta_time: float) -> Vector2:
	return current_recoil.lerp(Vector2.ZERO, clampf(decay_rate * delta_time, 0.0, 1.0))
