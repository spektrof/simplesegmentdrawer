#version 330

layout(location = 0) in vec2 vs_in_pos;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4( vs_in_pos.x, vs_in_pos.y, 0, 1);
}
