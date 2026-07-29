class_name DamageCalculator
extends RefCounted

# CS:GO Style Kevlar Health/Armor Damage Deduction Engine

enum HitGroup { GENERIC, HEAD, CHEST, STOMACH, LEFT_ARM, RIGHT_ARM, LEFT_LEG, RIGHT_LEG }

static func calculate_damage(base_damage: float, hit_group: HitGroup, has_kevlar: bool, armor_val: float) -> Dictionary:
	var multiplier: float = 1.0
	match hit_group:
		HitGroup.HEAD: multiplier = 4.0
		HitGroup.CHEST: multiplier = 1.0
		HitGroup.STOMACH: multiplier = 1.25
		_: multiplier = 0.75
		
	var raw_damage: float = base_damage * multiplier
	var final_hp_damage: float = raw_damage
	var final_armor_damage: float = 0.0
	
	if has_kevlar and armor_val > 0:
		# 70/30 health armor deduction ratio
		final_hp_damage = raw_damage * 0.70
		final_armor_damage = raw_damage * 0.30
		
	return {
		"hp_damage": final_hp_damage,
		"armor_damage": final_armor_damage
	}
