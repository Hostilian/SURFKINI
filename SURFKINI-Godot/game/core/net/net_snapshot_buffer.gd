class_name NetSnapshotBuffer
extends RefCounted

const BUFFER_SIZE: int = 128

var _snapshots: Array = []
var _head_index: int = 0

func _init() -> void:
	_snapshots.resize(BUFFER_SIZE)

func record_snapshot(tick: int, position: Vector3, velocity: Vector3, rotation: Vector3) -> void:
	var index: int = tick % BUFFER_SIZE
	_snapshots[index] = {
		"tick": tick,
		"position": position,
		"velocity": velocity,
		"rotation": rotation,
		"timestamp": Time.get_ticks_msec()
	}

func get_snapshot(tick: int) -> Dictionary:
	var index: int = tick % BUFFER_SIZE
	var snap = _snapshots[index]
	if snap != null and snap.get("tick", -1) == tick:
		return snap
	return {}
