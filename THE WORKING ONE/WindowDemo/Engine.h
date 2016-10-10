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

struct Token
{
	Model mod;
	bool visible;
};
struct Door
{
	Model mod;
	bool correctDoor;
};


class Engine
{
private:
	GLFWwindow* GLFWwindowPtr;
	ShaderManager shade = ShaderManager();
	Texture text = Texture();
	Camera cam = Camera();
	Model door1 = Model("Textures/portal.png", 3);
	Model door2 = Model("Textures/portal.png", 3);
	Model door3 = Model("Textures/portal.png", 3);

	Model token1 = Model("Textures/magic.jpg", 3);
	Model token2 = Model("Textures/magic.jpg", 3);
	Model token3 = Model("Textures/magic.jpg", 3);
	Model token4 = Model("Textures/magic.jpg", 3);
	Model token5 = Model("Textures/magic.jpg", 3);
	Model token6 = Model("Textures/magic.jpg", 3);
	Model token7 = Model("Textures/magic.jpg", 3);
	Model token8 = Model("Textures/magic.jpg", 3);
	Model token9 = Model("Textures/magic.jpg", 3);

	Model robit= Model("Textures/metal.jpg", 3);

	Model w1 = Model("Textures/floor.jpg", 3);
	Model w2 = Model("Textures/floor.jpg", 3);
	Model w3 = Model("Textures/floor.jpg", 3);
	Model w4 = Model("Textures/floor.jpg", 3);

	Model floor = Model("Textures/woodFloor.jpg", 3);

	time_t timer;
	double currTime;
	double deltaTime;
	double prevFrame;
	//Game game = Game();
	Token t1;
	Token t2;
	Token t3;
	Token t4;
	Token t5;
	Token t6;
	Token t7;
	Token t8;
	Token t9;

	Door d1;
	Door d2;
	Door d3;

	void collisions();
	void transMat();
	void render();
	void playerMove();
	void selectDoor();
	bool fpsEnable;
	void reset();

	int score;

public:
	Engine();
	~Engine();
	bool init();
	bool gameLoop();
	bool useShaders();
	bool loadModel();
	bool bufferModels();
};

