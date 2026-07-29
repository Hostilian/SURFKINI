class_name Speedometer
extends Control

@export var max_display_speed: float = 3500.0
var current_speed: float = 0.0

func _draw() -> void:
	# Draw circular speed gauge arc
	var center = size * 0.5
	var radius = minf(size.x, size.y) * 0.4
	var ratio = clampf(current_speed / max_display_speed, 0.0, 1.0)
	
	draw_arc(center, radius, deg_to_rad(135.0), deg_to_rad(405.0), 32, Color.DARK_GRAY, 6.0)
	draw_arc(center, radius, deg_to_rad(135.0), deg_to_rad(135.0 + (270.0 * ratio)), 32, Color.CYAN, 6.0)

func set_speed(spd: float) -> void:
	current_speed = spd
	queue_redraw()
