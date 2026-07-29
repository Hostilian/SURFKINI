class_name MacroRLAgent
extends Node

# Autonomous Surf Line Reinforcement Learning Optimizer

var q_table: Dictionary = {}

func get_best_action(state_hash: String) -> Vector3:
	if q_table.has(state_hash):
		return q_table[state_hash]
	return Vector3.FORWARD

func update_reward(state_hash: String, action: Vector3, reward_speed_gain: float) -> void:
	q_table[state_hash] = action
