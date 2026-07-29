class_name FPCamera
extends Camera3D

@export var mouse_sensitivity: float = 0.002
@export var fov_speed_scale: float = 0.01

var rot_x: float = 0.0
var rot_y: float = 0.0

func _ready() -> void:
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func _unhandled_input(event: InputEvent) -> void:
	if event is InputEventMouseMotion and Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		rot_y -= event.relative.x * mouse_sensitivity
		rot_x -= event.relative.y * mouse_sensitivity
		rot_x = clampf(rot_x, -deg_to_rad(89.0), deg_to_rad(89.0))
		
		transform.basis = Basis.from_euler(Vector3(rot_x, rot_y, 0.0))

func update_speed_fov(current_speed: float, base_fov: float = 75.0) -> void:
	var target_fov: float = clampf(base_fov + (current_speed * fov_speed_scale), base_fov, 110.0)
	fov = lerpf(fov, target_fov, 0.1)
