class_name EnvDetector
extends Node

static func is_web() -> bool:
	return OS.has_feature("web") or OS.get_name() == "Web"

static func is_mobile() -> bool:
	return OS.has_feature("mobile") or OS.get_name() in ["Android", "iOS"]

static func is_dedicated_server() -> bool:
	return DisplayServer.get_name() == "headless" or OS.has_feature("dedicated_server")

static func get_platform_info() -> Dictionary:
	return {
		"os_name": OS.get_name(),
		"is_web": is_web(),
		"is_mobile": is_mobile(),
		"is_server": is_dedicated_server(),
		"processor_count": OS.get_processor_count()
	}
