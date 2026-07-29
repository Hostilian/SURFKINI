class_name HitscanTracer
extends Node3D

static func perform_hitscan_query(space_state: PhysicsDirectSpaceState3D, origin: Vector3, direction: Vector3, range_len: float = 200.0) -> Dictionary:
	var query = PhysicsRayQueryParameters3D.create(origin, origin + (direction.normalized() * range_len))
	query.collide_with_areas = false
	query.collide_with_bodies = true
	
	var result = space_state.intersect_ray(query)
	if result.size() > 0:
		return {
			"hit": true,
			"collider": result.get("collider"),
			"position": result.get("position"),
			"normal": result.get("normal")
		}
	return {"hit": false}
