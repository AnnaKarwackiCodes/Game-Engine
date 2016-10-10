#include "Engine.h"


namespace 
{
	std::map<int, bool> keyIsDown;
	std::map<int, bool> keyWasDown;

	void mouseClick(GLFWwindow * windowPtr, int button, int action, int mods)
	{
		keyIsDown[button] = action;
	}
	void keyCallback(GLFWwindow* windowPtr, int key, int scancode, int action, int mods)
	{
		keyIsDown[key] = action;
	}
}



void Engine::collisions()
{
	// colliding with the doors
	//door 1
	if (robit.CollideWith(d1.mod) && d1.correctDoor)
	{
		//cout << "player hit the door 1" << endl;
		score += 100;
		cout << "TOTAL SCORE: " << score << endl;
		reset();
	}
	else if (robit.CollideWith(d1.mod) && d1.correctDoor == false)
	{
		cout << "You have chosen... poorly" << endl;
		cout << "GAME OVER" << endl;
		cout << "TOTAL SCORE: " << score << endl;
		glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
	}
	//door 2
	if (robit.CollideWith(d2.mod) && d2.correctDoor)
	{
		//cout << "player hit the door 2 " << endl;
		score += 100;
		cout << "TOTAL SCORE: " << score << endl;
		reset();
	}
	else if (robit.CollideWith(d2.mod) && d2.correctDoor == false)
	{
		cout << "You have chosen... poorly" << endl;
		cout << "GAME OVER" << endl;
		cout << "TOTAL SCORE: " << score << endl;
		glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
	}
	// door 3
	if (robit.CollideWith(d3.mod) && d3.correctDoor)
	{
		//cout << "player hit the door 3" << endl;
		score += 100;
		cout << "TOTAL SCORE: " << score << endl;
		reset();
	}
	else if (robit.CollideWith(d3.mod))
	{
		cout << "You have chosen... poorly" << endl;
		cout << "GAME OVER" << endl;
		cout << "TOTAL SCORE: " << score << endl;
		glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
	}
	// colliding with the tokens
	if (robit.CollideWith(t1.mod)&& t1.visible)
	{
		//cout << "player hit the token" << endl;
		score += 50;
		t1.visible = false;
	}
	if (robit.CollideWith(t2.mod) && t2.visible)
	{
		//cout << "player hit the token" << endl;
		score += 50;
		t2.visible = false;
	}
	if (robit.CollideWith(t3.mod) && t3.visible)
	{
		//cout << "player hit the token" << endl;
		score += 50;
		t3.visible = false;
	}
	if (robit.CollideWith(t4.mod) && t4.visible)
	{
		//cout << "player hit the token" << endl;
		score += 50;
		t4.visible = false;
	}
	if (robit.CollideWith(t5.mod) && t5.visible)
	{
		//cout << "player hit the token" << endl;
		score += 50;
		t5.visible = false;
	}
	if (robit.CollideWith(t6.mod) && t6.visible)
	{
		//cout << "player hit the token" << endl;
		score += 50;
		t6.visible = false;
	}
	if (robit.CollideWith(t7.mod) && t7.visible)
	{
		//cout << "player hit the token" << endl;
		score += 50;
		t7.visible = false;
	}
	if (robit.CollideWith(t8.mod) && t8.visible)
	{
		//cout << "player hit the token" << endl;
		score += 50;
		t8.visible = false;
	}
	if (robit.CollideWith(t9.mod) && t9.visible)
	{
		//cout << "player hit the token" << endl;
		score += 50;
		t9.visible = false;
	}

	// colliding with the wall
	if (robit.CollideWith(w1))
	{
		robit.newt(deltaTime, glm::vec3(0, .01, 0));
	}
	if (robit.CollideWith(w2))
	{
		robit.newt(deltaTime, glm::vec3(0, -.01, 0));
	}
	if (robit.CollideWith(w3))
	{
		robit.newt(deltaTime, glm::vec3(-.01,0, 0));
	}
	if (robit.CollideWith(w4))
	{
		robit.newt(deltaTime, glm::vec3(.01,0, 0));
	}
}

void Engine::transMat()
{
	d1.mod.transMat();
	d2.mod.transMat();
	d3.mod.transMat();
	t1.mod.transMat();
	t2.mod.transMat();
	t3.mod.transMat();
	t4.mod.transMat();
	t5.mod.transMat();
	t6.mod.transMat();
	t7.mod.transMat();
	t8.mod.transMat();
	t9.mod.transMat();
	robit.transMat();
	w1.transMat();
	w2.transMat();
	w3.transMat();
	w4.transMat();
	floor.transMat();
}

void Engine::render()
{
	d1.mod.render();
	d2.mod.render();
	d3.mod.render();
	if (t1.visible)
	{
		t1.mod.render();
	}
	if (t2.visible)
	{
		t2.mod.render();
	}
	if (t3.visible)
	{
		t3.mod.render();
	}
	if (t4.visible)
	{
		t4.mod.render();
	}
	if (t5.visible)
	{
		t5.mod.render();
	}
	if (t6.visible)
	{
		t6.mod.render();
	}
	if (t7.visible)
	{
		t7.mod.render();
	}
	if (t8.visible)
	{
		t8.mod.render();
	}
	if (t9.visible)
	{
		t9.mod.render();
	}
	robit.render();
	
	w1.render();
	w2.render();
	w3.render();
	w4.render();

	floor.render();
}

void Engine::playerMove()
{
	if (keyIsDown[GLFW_KEY_W] && keyWasDown == keyIsDown)
	{
		robit.newt(deltaTime, glm::vec3(0, 0.001,0));
		//cam.updateVel(glm::vec3(0, 0, .0000000001));
	}
	else if (keyIsDown[GLFW_KEY_S] && keyWasDown == keyIsDown)
	{
		robit.newt(deltaTime, glm::vec3(0,-0.001,0));
		//cam.updateVel(glm::vec3(0, 0, -.0000000001));
	}
	else if (keyIsDown[GLFW_KEY_D] && keyWasDown == keyIsDown)
	{
		robit.newt(deltaTime, glm::vec3(0.001, 0, 0));
		//cam.updateVel(glm::vec3(-.0000000001, 0, 0));

	}
	else if (keyIsDown[GLFW_KEY_A] && keyWasDown == keyIsDown)
	{
		robit.newt(deltaTime, glm::vec3(-0.001, 0, 0));
		//cam.updateVel(glm::vec3(.0000000001, 0, 0));
	}
	else
	{
		robit.clearVel();
		cam.clearVel();
	}
}

void Engine::selectDoor()
{
	srand(time(0));
	int correct = rand() % 3 + 1;

	switch (correct) {
	case 1:
		//cout << "Door 1 is correct door" << endl;
		d1.correctDoor = true;
		d2.correctDoor = false;
		d3.correctDoor = false;
		break;
	case 2:
		//cout << "Door 2 is correct door" << endl;
		d2.correctDoor = true;
		d1.correctDoor = false;
		d3.correctDoor = false;
		break;
	case 3:
		//cout << "Door 3 is correct door" << endl;
		d3.correctDoor = true;
		d1.correctDoor = false;
		d2.correctDoor = false;
	}
}

void Engine::reset()
{
	robit.obj.trans.location = glm::vec3(0, -1, -2);
	t1.visible = true;
	t2.visible = true;
	t3.visible = true;
	t4.visible = true;
	t5.visible = true;
	t6.visible = true;
	t7.visible = true;
	t8.visible = true;
	t9.visible = true;
	selectDoor();
}

Engine::Engine()
{
	t1.mod = token1;
	t1.visible = true;
	t2.mod = token1;
	t2.visible = true;
	t3.mod = token1;
	t3.visible = true;
	t4.mod = token1;
	t4.visible = true;
	t5.mod = token1;
	t5.visible = true;
	t6.mod = token1;
	t6.visible = true;
	t7.mod = token1;
	t7.visible = true;
	t8.mod = token1;
	t8.visible = true;
	t9.mod = token1;
	t9.visible = true;

	d1.mod = door1;
	d2.mod = door2;
	d3.mod = door3;
	
	selectDoor();
}


Engine::~Engine()
{
}

bool Engine::init()
{
	//Initialize the window library.
	if (glfwInit() == GL_FALSE)
	{
		return false;
	}

	//create a windowed mode window
	GLFWwindowPtr = glfwCreateWindow(900, 600, "Anna Karwacki DSA1 Engine", NULL, NULL);

	//Make it the currently active window, or quit
	if (GLFWwindowPtr != nullptr)
		glfwMakeContextCurrent(GLFWwindowPtr);
	else
	{
		glfwTerminate();
		return false;
	}

	// Initialize GLEW or quit
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	glfwSetKeyCallback(GLFWwindowPtr, keyCallback);
	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); wireframe
	fpsEnable = false;

	return true;
}



bool Engine::gameLoop()
{
	currTime = glfwGetTime();
	prevFrame = currTime;

	glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// loop until the user closes the window
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		// Update physical simulation
		// Draw buffered models
		// process input/window events
		// Processs queued window, mouse & keyboard callback events
		// clear the canvas
		currTime = glfwGetTime();
		deltaTime = currTime - prevFrame;
		prevFrame = currTime;

		playerMove();

		if (fpsEnable)
		{
			cam.FPSControl(GLFWwindowPtr);
		}

		transMat();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		collisions();
		

		cam.calcMat(robit.obj.trans.location);
		cam.updateTrans(deltaTime);
		cam.uploadMat();

		render();
		
	
		glm::vec3 lightLoc = glm::vec3(0, 1, 1);
		glUniform3f(5, lightLoc.x, lightLoc.y, lightLoc.z);

		if (keyIsDown[GLFW_KEY_ESCAPE])
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
		}

		if (keyIsDown[GLFW_KEY_F])
		{
			fpsEnable = !fpsEnable;
		}
		// unbind an object after drawing it

		glfwSwapBuffers(GLFWwindowPtr);
		keyWasDown = keyIsDown;
		glfwPollEvents();
	}

	glfwTerminate();
	return false;
}

bool Engine::useShaders()
{
	if (shade.loadShaders("shaders/vShader.glsl", "shaders/fShader.glsl"))
	{
		glUseProgram(shade.getProgram());
		return true;
	}
	return false;
}

bool Engine::loadModel()
{
	bufferModels();
	d1.mod.setup(glm::vec3(-1, 1, -2), glm::vec3(0, 0, 0), glm::vec3(.06, .03, .1));
	d2.mod.setup(glm::vec3(0, 1, -2), glm::vec3(0, 0, 0), glm::vec3(.06, .03, .1));
	d3.mod.setup(glm::vec3(1, 1, -2), glm::vec3(0, 0, 0), glm::vec3(.06, .03, .1));

	t1.mod.setup(glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1));
	t2.mod.setup(glm::vec3(-1, 0, -2), glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1));
	t3.mod.setup(glm::vec3(1, 0, -2), glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1));
	t4.mod.setup(glm::vec3(0, -.5, -2), glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1));
	t5.mod.setup(glm::vec3(-1, -.5, -2), glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1));
	t6.mod.setup(glm::vec3(1, -.5, -2), glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1));
	t7.mod.setup(glm::vec3(0, .5, -2), glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1));
	t8.mod.setup(glm::vec3(-1, .5, -2), glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1));
	t9.mod.setup(glm::vec3(1, .5, -2), glm::vec3(0, 0, 0), glm::vec3(.1, .1, .1));

	robit.setup(glm::vec3(0, -1, -2), glm::vec3(0, 1.2, 0), glm::vec3(.1, .1, .1));
					// x   y   z
	w1.setup(glm::vec3(0, -1.2, -2), glm::vec3(0, 0, 0), glm::vec3(2, .1, .2));
	w2.setup(glm::vec3(0, 1.2, -2), glm::vec3(0, 0, 0), glm::vec3(2, .1, .2));
	w3.setup(glm::vec3(1.6, 0, -2), glm::vec3(0, 0, 0), glm::vec3(.1, 2, .2));
	w4.setup(glm::vec3(-1.6, 0, -2), glm::vec3(0, 0, 0), glm::vec3(.1, 2, .2));

	floor.setup(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0), glm::vec3(3, 3, .1));
	return true;
}

bool Engine::bufferModels()
{
	d1.mod.bufferModel("models/box.obj");
	d2.mod.bufferModel("models/box.obj");
	d3.mod.bufferModel("models/box.obj");

	t1.mod.bufferModel("models/sphere.obj");
	t2.mod.bufferModel("models/sphere.obj");
	t3.mod.bufferModel("models/sphere.obj");
	t4.mod.bufferModel("models/sphere.obj");
	t5.mod.bufferModel("models/sphere.obj");
	t6.mod.bufferModel("models/sphere.obj");
	t7.mod.bufferModel("models/sphere.obj");
	t8.mod.bufferModel("models/sphere.obj");
	t9.mod.bufferModel("models/sphere.obj");

	robit.bufferModel("models/NewRobit2.obj");

	w1.bufferModel("models/box.obj");
	w2.bufferModel("models/box.obj");
	w3.bufferModel("models/box.obj");
	w4.bufferModel("models/box.obj");

	floor.bufferModel("models/box.obj");
	return false;
}



