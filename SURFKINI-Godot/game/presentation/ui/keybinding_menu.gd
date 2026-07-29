class_name KeybindingMenu
extends Control

signal keybound(action_name: String, key_event: InputEvent)

func remap_action_key(action_name: String, new_event: InputEvent) -> void:
	if InputMap.has_action(action_name):
		InputMap.action_erase_events(action_name)
		InputMap.action_add_event(action_name, new_event)
		keybound.emit(action_name, new_event)
