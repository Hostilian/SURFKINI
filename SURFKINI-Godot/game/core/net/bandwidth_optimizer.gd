class_name BandwidthOptimizer
extends RefCounted

# Adaptive Delta Compression for Network RPC Stream

static func quantize_position(pos: Vector3, precision: float = 0.01) -> Vector3:
	return Vector3(
		snappedf(pos.x, precision),
		snappedf(pos.y, precision),
		snappedf(pos.z, precision)
	)

static func should_send_update(prev_pos: Vector3, curr_pos: Vector3, min_delta_sqr: float = 0.0001) -> bool:
	return prev_pos.distance_squared_to(curr_pos) >= min_delta_sqr
