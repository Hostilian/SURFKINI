class_name TelemetryZone
extends Area3D

signal telemetry_recorded(speed_u_s: float, entry_angle_deg: float)

func _ready() -> void:
	body_entered.connect(_on_body_entered)

func _on_body_entered(body: Node) -> void:
	if body.is_in_group("players") and body.has_method("get_linear_velocity"):
		var vel: Vector3 = body.get_linear_velocity()
		var speed: float = vel.length()
		var angle: float = rad_to_deg(Vector3.FORWARD.angle_to(vel.normalized()))
		telemetry_recorded.emit(speed, angle)
