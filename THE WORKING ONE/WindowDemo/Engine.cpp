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



Engine::Engine()
{
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

		if (keyIsDown[GLFW_KEY_W] && keyWasDown == keyIsDown)
		{
			mod3.newt(deltaTime, glm::vec3(0, 0.001, 0));
		}
		else if (keyIsDown[GLFW_KEY_S] && keyWasDown == keyIsDown)
		{
			mod3.newt(deltaTime, glm::vec3(0, -0.001, 0));
		}
		else if (keyIsDown[GLFW_KEY_D] && keyWasDown == keyIsDown)
		{
			mod3.newt(deltaTime, glm::vec3(0.001, 0, 0));
		}
		else if (keyIsDown[GLFW_KEY_A] && keyWasDown == keyIsDown)
		{
			mod3.newt(deltaTime, glm::vec3(-0.001, 0, 0));
		}
		else 
		{
			mod3.clearVel();
		}
		mod1.transMat();
		mod2.transMat();
		mod3.transMat();

		glClear(GL_COLOR_BUFFER_BIT);

		if (mod1.CollideWith(mod3))
		{
			cout << "Pikachu hit door 1" << endl;
			mod1.TextureChange("opendoor.jpg");
		}
		else
		{
			mod1.TextureChange("door.jpg");
		}
		if (mod2.CollideWith(mod3))
		{
			cout << "Pikachu hit door 2" << endl;
			mod2.TextureChange("opendoor.jpg");
		}
		else
		{
			mod2.TextureChange("door.jpg");
		}

		cam.FPSControl(GLFWwindowPtr);
		if (keyIsDown[GLFW_KEY_LEFT])
		{
			cam.updateTrans(deltaTime, glm::vec3(glm::vec3(-1, 0, 0)));
			cout << "left" << endl;
		}
		if (keyIsDown[GLFW_KEY_RIGHT])
		{
			cam.updateTrans(deltaTime, glm::vec3(glm::vec3(1, 0, 0)));
			cout << "right" << endl;
		}
		if (keyIsDown[GLFW_KEY_UP])
		{
			cam.updateTrans(deltaTime, glm::vec3(glm::vec3(0, 0, -1)));
			cout << "up" << endl;
		}
		if (keyIsDown[GLFW_KEY_DOWN])
		{
			cam.updateTrans(deltaTime, glm::vec3(glm::vec3(0, 0, 1)));
			cout << "down" << endl;
		}
		cam.calcMat();
		cam.uploadMat();
		

		
		mod1.render();
		mod2.render();
		mod3.render();
	
		

		if (keyIsDown[GLFW_KEY_ESCAPE])
		{
			glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
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
	mod1.setup();
	mod2.setup(glm::vec3(0.5, 0.5, 0), glm::vec3(0, 0, 0), glm::vec3(.2, .2, .2));
	mod3.setup(glm::vec3(-0.5, -0.5, 0), glm::vec3(0, 0, 0), glm::vec3(.2, .2, .2));
	return true;
}



