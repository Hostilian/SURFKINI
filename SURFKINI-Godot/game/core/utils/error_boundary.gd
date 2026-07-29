class_name ErrorBoundary
extends Node

# Graceful Degradation & Resilience System for SURFKINI
# Source: EUshop Graceful Degradation & Resilience Patterns

signal error_caught(error_message: String, stack_trace: Array)

static var is_degraded_mode: bool = false
static var error_count: int = 0

func catch_error(module_name: String, error_msg: String) -> void:
	error_count += 1
	printerr("[ErrorBoundary] [%s] %s" % [module_name, error_msg])
	
	if error_count >= 3:
		is_degraded_mode = true
		print("[ErrorBoundary] Enabling Degraded Mode (Low VFX / Simplified Netcode)")
		
	error_caught.emit(error_msg, get_stack())

static func reset_error_state() -> void:
	error_count = 0
	is_degraded_mode = false
