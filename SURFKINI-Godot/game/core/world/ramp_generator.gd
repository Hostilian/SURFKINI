class_name RampGenerator
extends Node3D

@export var ramp_length: float = 50.0
@export var ramp_height: float = 15.0
@export var ramp_width: float = 4.0
@export var incline_angle_deg: float = 45.0

func generate_surf_ramp_mesh() -> ArrayMesh:
	var st = SurfaceTool.new()
	st.begin(Mesh.PRIMITIVE_TRIANGLES)
	
	var rad: float = deg_to_rad(incline_angle_deg)
	var normal: Vector3 = Vector3(cos(rad), sin(rad), 0.0).normalized()
	
	# Simple wedge surf ramp geometry
	var p0 = Vector3(0, 0, 0)
	var p1 = Vector3(ramp_width, ramp_height, 0)
	var p2 = Vector3(0, 0, ramp_length)
	var p3 = Vector3(ramp_width, ramp_height, ramp_length)
	
	st.set_normal(normal)
	st.add_vertex(p0)
	st.add_vertex(p1)
	st.add_vertex(p2)
	
	st.add_vertex(p1)
	st.add_vertex(p3)
	st.add_vertex(p2)
	
	return st.commit()
