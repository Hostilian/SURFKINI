class_name SaveManager
extends Node

const SAVE_PATH: String = "user://surf_pb_save.json"

static func save_pb_records(records: Dictionary) -> bool:
	var file = FileAccess.open(SAVE_PATH, FileAccess.WRITE)
	if file:
		var json_str = JSON.stringify(records, "  ")
		file.store_string(json_str)
		file.close()
		return true
	return false

static func load_pb_records() -> Dictionary:
	if not FileAccess.file_exists(SAVE_PATH):
		return {}
		
	var file = FileAccess.open(SAVE_PATH, FileAccess.READ)
	if file:
		var json_str = file.get_as_text()
		file.close()
		var json = JSON.new()
		if json.parse(json_str) == OK and json.data is Dictionary:
			return json.data
	return {}
