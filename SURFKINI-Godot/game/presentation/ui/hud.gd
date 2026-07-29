class_name HUD
extends CanvasLayer

@onready var speed_label: Label = $SpeedLabel
@onready var timer_label: Label = $TimerLabel
@onready var key_w: ColorRect = $KeyOverlay/KeyW
@onready var key_a: ColorRect = $KeyOverlay/KeyA
@onready var key_s: ColorRect = $KeyOverlay/KeyS
@onready var key_d: ColorRect = $KeyOverlay/KeyD

func update_speed(speed: float) -> void:
	if speed_label:
		speed_label.text = "%.0f u/s" % speed

func update_timer_display(time_ms: int) -> void:
	if timer_label:
		var mins = time_ms / 60000
		var secs = (time_ms % 60000) / 1000
		var ms = time_ms % 1000
		timer_label.text = "%02d:%02d.%03d" % [mins, secs, ms]

func update_key_overlay(move_vec: Vector2) -> void:
	if key_w: key_w.color = Color.GREEN if move_vec.y > 0 else Color.DARK_GRAY
	if key_s: key_s.color = Color.GREEN if move_vec.y < 0 else Color.DARK_GRAY
	if key_a: key_a.color = Color.GREEN if move_vec.x < 0 else Color.DARK_GRAY
	if key_d: key_d.color = Color.GREEN if move_vec.x > 0 else Color.DARK_GRAY
