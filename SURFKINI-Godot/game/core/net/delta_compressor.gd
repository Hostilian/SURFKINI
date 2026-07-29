class_name DeltaCompressor
extends RefCounted

# XOR Network Snapshot Delta Compression Engine

static func compress_delta(base_state: int, new_state: int) -> int:
	return base_state ^ new_state

static func decompress_delta(base_state: int, delta_state: int) -> int:
	return base_state ^ delta_state
