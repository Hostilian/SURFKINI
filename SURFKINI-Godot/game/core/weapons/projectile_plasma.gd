class_name ProjectilePlasma
extends Node3D

# Plasma Energy Projectile Trajectory Solver Node

@export var speed: float = 1200.0
@export var damage: float = 45.0

func _physics_process(delta: float) -> void:
	global_position += -global_transform.basis.z * speed * delta
