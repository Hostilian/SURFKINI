class_name SurfRampTagging
extends RefCounted

# Surface Normal Slope Query for Surfability Checks (42 deg to 70 deg)

static func is_surface_surfable(surface_normal: Vector3) -> bool:
	var incline_rad: float = surface_normal.angle_to(Vector3.UP)
	var incline_deg: float = rad_to_deg(incline_rad)
	return incline_deg >= 42.0 and incline_deg <= 70.0
