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
#include "Texture.h"
#include "Model.h"
#include "Camera.h"

#include <iostream>
#include <map>
#include <time.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Engine
{
private:
	GLFWwindow* GLFWwindowPtr;
	ShaderManager shade = ShaderManager();
	Texture text = Texture();
	Camera cam = Camera();
	Model mod1 = Model("Textures/door.jpg", 3);
	Model mod2 = Model("Textures/door.jpg", 3);
	Model mod3 = Model("Textures/pika.png", 2);
	time_t timer;
	double currTime;
	double deltaTime;
	double prevFrame;

public:
	Engine();
	~Engine();
	bool init();
	bool gameLoop();
	bool useShaders();
	bool loadModel();
	
};

