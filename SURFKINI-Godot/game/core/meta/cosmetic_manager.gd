class_name CosmeticManager
extends Node

signal cosmetic_unlocked(cosmetic_id: String)

var unlocked_cosmetics: Array = ["trail_default", "hud_cyan"]

func check_pb_unlocks(personal_best_ms: int) -> void:
	if personal_best_ms < 60000 and not "trail_fire" in unlocked_cosmetics:
		unlocked_cosmetics.append("trail_fire")
		cosmetic_unlocked.emit("trail_fire")
		
	if personal_best_ms < 45000 and not "title_surf_god" in unlocked_cosmetics:
		unlocked_cosmetics.append("title_surf_god")
		cosmetic_unlocked.emit("title_surf_god")
