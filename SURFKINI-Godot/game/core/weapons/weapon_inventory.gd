class_name WeaponInventory
extends Node

# Player Weapon Slot Management & Fast Switching

var primary_weapon: String = "AK47"
var secondary_weapon: String = "USP"
var active_slot: int = 1

func select_slot(slot: int) -> String:
	active_slot = slot
	return primary_weapon if active_slot == 1 else secondary_weapon
