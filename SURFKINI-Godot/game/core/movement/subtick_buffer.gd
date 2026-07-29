class_name SubtickBuffer
extends RefCounted

# 8ms Subtick Jump Buffer & 100ms Coyote Time Grace Window

const JUMP_BUFFER_MS: int = 80 # 80ms jump input buffer window
const COYOTE_TIME_MS: int = 100 # 100ms grace window on ramp exit

var last_jump_press_ms: int = -99999
var last_grounded_ms: int = 0

func record_jump_press() -> void:
	last_jump_press_ms = Time.get_ticks_msec()

func record_grounded() -> void:
	last_grounded_ms = Time.get_ticks_msec()

func can_buffered_jump(current_time_ms: int) -> bool:
	var buffer_valid: bool = (current_time_ms - last_jump_press_ms) <= JUMP_BUFFER_MS
	var coyote_valid: bool = (current_time_ms - last_grounded_ms) <= COYOTE_TIME_MS
	return buffer_valid and coyote_valid
