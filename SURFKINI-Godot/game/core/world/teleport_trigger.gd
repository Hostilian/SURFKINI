class_name TeleportTrigger
extends Area3D

# Stage Exit & Failure Zone Restart Teleport Node

@export var destination_point: Vector3 = Vector3.ZERO

func _on_body_entered(body: Node3D) -> void:
	if body.has_method("teleport_to"):
		body.call("teleport_to", destination_point)
