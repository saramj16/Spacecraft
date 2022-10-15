#version 330

in vec3 v_normal;
in vec3 v_camera;
in vec2 v_uv;

uniform vec3 u_light;
uniform sampler2D u_texture_diffuse;

out vec4 fragColor;

void main(void)
{
	vec3 final_color = vec3(0.1, 0.1, 0.1);


	// simple red colour
	 fragColor =  vec4(texture2D(u_texture_diffuse, v_uv).xyz, 1.0);
}
