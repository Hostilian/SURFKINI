class_name BoosterRing
extends Area3D

@export var boost_speed_impulse: float = 800.0

func _ready() -> void:
	body_entered.connect(_on_body_entered)

func _on_body_entered(body: Node) -> void:
	if body.is_in_group("players") and body.has_method("apply_speed_boost"):
		var boost_dir: Vector3 = global_transform.basis.z.normalized()
		body.apply_speed_boost(boost_dir * boost_speed_impulse)
