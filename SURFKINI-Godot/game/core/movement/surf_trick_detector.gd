class_name SurfTrickDetector
extends RefCounted

# Surf Trick Detection (360/720 Spin, Speed Milestones)

var accumulated_rotation_deg: float = 0.0
var max_run_speed: float = 0.0

func process_frame(delta_yaw_deg: float, current_speed: float) -> Dictionary:
	accumulated_rotation_deg += absf(delta_yaw_deg)
	max_run_speed = maxf(max_run_speed, current_speed)
	
	var trick_detected: String = ""
	if accumulated_rotation_deg >= 720.0:
		trick_detected = "720 Spin!"
		accumulated_rotation_deg = 0.0
	elif accumulated_rotation_deg >= 360.0:
		trick_detected = "360 Spin!"
		accumulated_rotation_deg -= 360.0
		
	return {
		"trick": trick_detected,
		"max_speed": max_run_speed,
		"accumulated_rotation": accumulated_rotation_deg
	}
