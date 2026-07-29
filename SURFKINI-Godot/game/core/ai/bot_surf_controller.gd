class_name BotSurfController
extends Node

@export var bot_name: String = "SurfBot-9000"
@export var skill_level: float = 1.0 # 0.0 (novice) to 1.0 (pro)

var target_ramp_normal: Vector3 = Vector3.UP
var wish_direction: Vector3 = Vector3.FORWARD

func calculate_optimal_strafe(current_velocity: Vector3, ramp_normal: Vector3) -> Vector3:
	var side_dir: Vector3 = ramp_normal.cross(Vector3.UP).normalized()
	if current_velocity.dot(side_dir) < 0:
		side_dir = -side_dir
		
	# Blend strafe input based on bot skill
	return side_dir.lerp(Vector3.FORWARD, 1.0 - skill_level).normalized()
