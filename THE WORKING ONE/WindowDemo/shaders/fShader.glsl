#version 430
uniform sampler2D myTexture;

//new stuff

	layout (location = 5) uniform vec3 lightLoc;
	layout (location = 6) uniform vec3 cameraLoc;
	
	in vec3 worldLoc;
	in vec2 fragUV;
	in vec3 worldNorm;

void main()
{
//new stuff
	vec3 L = normalize( lightLoc - worldLoc);
	vec3 V = normalize(cameraLoc - worldLoc);
	vec3 H = normalize(L + V);
	vec3 N = normalize(worldNorm);
	
	float amb = .2;
	float dif = 1 * max(dot(L,N),0);
	float spec = 0 * pow(max(dot(H,N),0),16);
	float bright = amb + dif + spec;
	
	vec4 texColor = texture(myTexture,fragUV);
	
	gl_FragColor = vec4(bright * texColor.rgb, texColor.a);
	//gl_FragColor = vec4(worldNorm, 1);
}