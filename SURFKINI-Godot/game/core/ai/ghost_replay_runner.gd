class_name GhostReplayRunner
extends Node3D

var _replay_frames: Array = []
var _current_frame_idx: int = 0
var _is_playing: bool = false

func load_replay(frames: Array) -> void:
	_replay_frames = frames
	_current_frame_idx = 0
	_is_playing = true

func update_ghost(delta_time: float) -> void:
	if not _is_playing or _replay_frames.is_empty():
		return
		
	if _current_frame_idx < _replay_frames.size():
		var frame = _replay_frames[_current_frame_idx]
		global_position = frame.get("pos", Vector3.ZERO)
		_current_frame_idx += 1
	else:
		_is_playing = false
