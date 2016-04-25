#version 430

out vec2 fragUV;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvPosition;
layout (location = 3) uniform mat4 worldTransform;

void main()
{
	gl_Position = worldTransform * vec4(position, 1);
	fragUV = uvPosition;
	
}