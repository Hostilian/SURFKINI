class_name BotDifficultyManager
extends Node

enum Difficulty { EASY, MEDIUM, HARD, EXPERT }

static func get_difficulty_parameters(diff: Difficulty) -> Dictionary:
	match diff:
		Difficulty.EASY:
			return {"strafe_error_pct": 25.0, "max_speed_cap": 1200.0, "reaction_ms": 300}
		Difficulty.MEDIUM:
			return {"strafe_error_pct": 12.0, "max_speed_cap": 2000.0, "reaction_ms": 200}
		Difficulty.HARD:
			return {"strafe_error_pct": 5.0, "max_speed_cap": 2800.0, "reaction_ms": 100}
		Difficulty.EXPERT:
			return {"strafe_error_pct": 0.0, "max_speed_cap": 3500.0, "reaction_ms": 50}
	return {"strafe_error_pct": 12.0, "max_speed_cap": 2000.0, "reaction_ms": 200}
