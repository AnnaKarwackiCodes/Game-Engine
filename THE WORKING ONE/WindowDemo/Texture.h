#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "FreeImage.h"

#include <vector>
#include <string>

#include "ShaderManager.h"

#include <iostream>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Texture
{
public:
	Texture();
	~Texture();
	//vector<unsigned int> textures;
	bool loadTexture(char* name);
	int texIndex;
	unsigned int texID;

private:
	
};

