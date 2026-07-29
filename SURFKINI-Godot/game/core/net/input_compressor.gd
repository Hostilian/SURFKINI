class_name InputCompressor
extends RefCounted

# Bitfield quantization for movement RPC inputs
const FLAG_FORWARD: int = 1 << 0
const FLAG_BACKWARD: int = 1 << 1
const FLAG_LEFT: int     = 1 << 2
const FLAG_RIGHT: int    = 1 << 3
const FLAG_JUMP: int     = 1 << 4
const FLAG_CROUCH: int   = 1 << 5

static func pack_input(forward: bool, back: bool, left: bool, right: bool, jump: bool, crouch: bool) -> int:
	var bits: int = 0
	if forward: bits |= FLAG_FORWARD
	if back:    bits |= FLAG_BACKWARD
	if left:    bits |= FLAG_LEFT
	if right:   bits |= FLAG_RIGHT
	if jump:    bits |= FLAG_JUMP
	if crouch:  bits |= FLAG_CROUCH
	return bits

static func unpack_input(bits: int) -> Dictionary:
	return {
		"forward": (bits & FLAG_FORWARD) != 0,
		"back":    (bits & FLAG_BACKWARD) != 0,
		"left":    (bits & FLAG_LEFT) != 0,
		"right":   (bits & FLAG_RIGHT) != 0,
		"jump":    (bits & FLAG_JUMP) != 0,
		"crouch":  (bits & FLAG_CROUCH) != 0,
	}
