class_name SurfkiniGameInstance
extends Node

# Global SURFKINI Game Instance Lifecycle & Session State Manager

static var instance: SurfkiniGameInstance = null

var current_session_id: String = ""
var is_network_connected: bool = true

func _ready() -> void:
	instance = self
	current_session_id = "Session_%d" % Time.get_ticks_msec()
	print("[SurfkiniGameInstance] Session initialized: %s" % current_session_id)
