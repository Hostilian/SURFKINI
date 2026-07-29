class_name ReplayRecorder
extends Node

# Input Stream .surf Binary Replay File Recorder

var recorded_ticks: Array = []

func record_tick_input(tick: int, wish_dir: Vector3, buttons: int) -> void:
	recorded_ticks.append({
		"tick": tick,
		"wish_dir": wish_dir,
		"buttons": buttons
	})
