class_name AudioManager
extends Node

# Spatial 3D Audio & Dynamic Wind Pitch Controller

@export var wind_sfx_player: AudioStreamPlayer
@export var min_wind_speed: float = 300.0
@export var max_wind_speed: float = 3500.0

func update_wind_audio(current_speed: float) -> void:
	if not wind_sfx_player: return
	
	if current_speed < min_wind_speed:
		wind_sfx_player.volume_db = -80.0 # Mute
	else:
		var ratio: float = clampf((current_speed - min_wind_speed) / (max_wind_speed - min_wind_speed), 0.0, 1.0)
		wind_sfx_player.volume_db = lerpf(-30.0, 0.0, ratio)
		wind_sfx_player.pitch_scale = lerpf(0.8, 1.5, ratio)
