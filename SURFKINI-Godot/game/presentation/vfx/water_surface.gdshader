shader_type spatial;

uniform vec4 water_color : source_color = vec4(0.0, 0.4, 0.8, 0.8);
uniform float wave_speed = 1.0;

void fragment() {
	vec2 uv = UV + vec2(TIME * wave_speed * 0.05, TIME * wave_speed * 0.03);
	float wave = sin(uv.x * 20.0) * cos(uv.y * 20.0);
	
	ALBEDO = water_color.rgb + vec3(wave * 0.1);
	ALPHA = water_color.a;
	ROUGHNESS = 0.1;
	SPECULAR = 0.8;
}
