class_name SurfPhysicsSolver
extends RefCounted

# Source Engine Surf Physics Math (Clean-Room GDScript Port)
# Source: Valve Source Engine SDK (PM_Accelerate, ClipVelocity, PM_Friction)

const GRAVITY: float = 800.0
const AIR_ACCEL: float = 150.0
const MAX_AIR_SPEED: float = 30.0
const STOP_SPEED: float = 100.0

static func clip_velocity(in_vel: Vector3, normal: Vector3, overbounce: float = 1.0) -> Vector3:
	var backoff: float = in_vel.dot(normal)
	if backoff < 0.0:
		backoff *= overbounce
	else:
		backoff /= overbounce
	return in_vel - (normal * backoff)

static func air_accelerate(in_vel: Vector3, wish_dir: Vector3, wish_speed: float, accel: float, delta_time: float) -> Vector3:
	var wish_spd: float = minf(wish_speed, MAX_AIR_SPEED)
	var current_spd: float = in_vel.dot(wish_dir)
	var add_speed: float = wish_spd - current_spd
	
	if add_speed <= 0.0:
		return in_vel
		
	var accel_speed: float = accel * wish_speed * delta_time
	accel_speed = minf(accel_speed, add_speed)
	return in_vel + (wish_dir * accel_speed)

static func apply_friction(in_vel: Vector3, friction: float, delta_time: float) -> Vector3:
	var speed: float = in_vel.length()
	if speed < 0.1:
		return Vector3.ZERO
		
	var control: float = maxf(speed, STOP_SPEED)
	var drop: float = control * friction * delta_time
	var new_speed: float = maxf(speed - drop, 0.0)
	
	if speed > 0.0:
		new_speed /= speed
	return in_vel * new_speed
