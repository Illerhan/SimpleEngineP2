// request GLSL 3.3
#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

in vec3 in Position;

void main ()
{
	vec4 pos = vac4(inPosition, 1.0);
	glPosition = pos * uWorldTransform * uViewProj;
}