class_name Logger
extends Node

enum LogLevel { DEBUG, INFO, WARNING, ERROR }

static var current_level: LogLevel = LogLevel.INFO

static func log_info(module: String, message: String) -> void:
	if current_level <= LogLevel.INFO:
		print("[%s] [INFO] %s" % [module, message])

static func log_warning(module: String, message: String) -> void:
	if current_level <= LogLevel.WARNING:
		print_rich("[color=yellow][%s] [WARN] %s[/color]" % [module, message])

static func log_error(module: String, message: String) -> void:
	if current_level <= LogLevel.ERROR:
		printerr("[%s] [ERROR] %s" % [module, message])

static func log_debug(module: String, message: String) -> void:
	if current_level <= LogLevel.DEBUG:
		print("[%s] [DEBUG] %s" % [module, message])
