#version 330

uniform vec3 COLOR = vec3(1,0,0);

out vec4 _color;

void main()
{

	_color =   vec4(COLOR,1);
}