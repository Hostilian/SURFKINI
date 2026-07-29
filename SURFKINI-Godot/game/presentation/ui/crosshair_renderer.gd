class_name CrosshairRenderer
extends Control

@export var crosshair_color: Color = Color.GREEN
@export var base_gap: float = 4.0
@export var line_length: float = 8.0
@export var line_width: float = 2.0

var current_gap: float = 4.0

func _draw() -> void:
	var center = size * 0.5
	
	# Top line
	draw_line(center - Vector2(0, current_gap + line_length), center - Vector2(0, current_gap), crosshair_color, line_width)
	# Bottom line
	draw_line(center + Vector2(0, current_gap), center + Vector2(0, current_gap + line_length), crosshair_color, line_width)
	# Left line
	draw_line(center - Vector2(current_gap + line_length, 0), center - Vector2(current_gap, 0), crosshair_color, line_width)
	# Right line
	draw_line(center + Vector2(current_gap, 0), center + Vector2(current_gap + line_length, 0), crosshair_color, line_width)

func update_recoil_bloom(recoil_pct: float) -> void:
	current_gap = base_gap + (recoil_pct * 12.0)
	queue_redraw()
