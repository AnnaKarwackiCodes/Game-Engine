#version 430



layout (location = 0) in vec3 modelLocation;
layout (location = 1) in vec2 modelUV;
layout (location = 2) in vec3 modelNorm;

layout (location = 3) uniform mat4 worldTransform;
layout (location = 4) uniform mat4 cameraMat;

//world space
out vec3 worldLoc;
out vec2 fragUV;
out vec3 worldNorm;
void main()
{
	
	//new stuff
	worldLoc = (worldTransform * vec4(modelLocation,1)).xyz;
	fragUV = modelUV;
	vec4 fash = inverse(transpose(worldTransform))*vec4(modelNorm, 0);
	worldNorm = vec3(fash);
	
	
	//view space
	gl_Position = cameraMat * vec4(worldLoc,1);
	
}