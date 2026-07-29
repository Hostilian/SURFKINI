class_name BotSpawner
extends Node

# Multi-Agent Bot Match Population Spawner

var spawned_bots: Array = []

func spawn_bot_wave(count: int) -> int:
	for i in range(count):
		spawned_bots.append("Bot_%d" % i)
	return spawned_bots.size()
