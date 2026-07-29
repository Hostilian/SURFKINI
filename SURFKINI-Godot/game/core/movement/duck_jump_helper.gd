class_name DuckJumpHelper
extends RefCounted

# Duck-Jump Crouch Bounding Box Height Offset Engine

const STANDING_HEIGHT: float = 1.8
const CROUCHING_HEIGHT: float = 1.2

static func calculate_eye_offset(is_crouching: bool, crouch_ratio: float) -> float:
	var target_height: float = lerp(STANDING_HEIGHT, CROUCHING_HEIGHT, clamp(crouch_ratio, 0.0, 1.0))
	return target_height * 0.85
