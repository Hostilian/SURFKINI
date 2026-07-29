class_name RampParticleTrail
extends GPUParticles3D

@export var min_emitting_speed: float = 500.0

func update_trail(is_on_ramp: bool, current_speed: float) -> void:
	emitting = is_on_ramp and (current_speed >= min_emitting_speed)
