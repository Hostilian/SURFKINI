shader_type canvas_item;

uniform float speed_intensity : hint_range(0.0, 1.0) = 0.0;
uniform vec4 line_color : source_color = vec4(1.0, 1.0, 1.0, 0.4);

void fragment() {
	vec2 center = vec2(0.5, 0.5);
	vec2 uv = UV - center;
	float dist = length(uv);
	
	float angle = atan(uv.y, uv.x);
	float lines = sin(angle * 40.0 + TIME * 30.0);
	
	float mask = smoothstep(0.25, 0.5, dist) * step(0.7, lines);
	COLOR = line_color * mask * speed_intensity;
}
