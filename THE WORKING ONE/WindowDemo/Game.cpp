#include "Game.h"

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

Game::Game()
{
	//set up where everything goes, default locations
	//player stuff
	robit.location = glm::vec3(0, 0, -.8);
	robit.mod = Model("Textures/metal.jpg", 3);
	//door stuff
	//d1.location = glm::vec3(-0.2, .9, 0);
	//d1.mod = Model("Textures/wood.jpg", 3);
	//d2.location = glm::vec3(0, .9, 0);
	//d2.mod = Model("Textures/wood.jpg", 3);
	//d3.location = glm::vec3(.2, .9, 0);
	//d3.mod = Model("Textures/wood.jpg", 3);
	////token stuff
	//t1.location = glm::vec3(.2, .2, 0);
	//t1.mod = Model("Textures/magic.jpg", 2);
	//t2.location = glm::vec3(.2, .4, 0);
	//t2.mod = Model("Textures/magic.jpg", 2);
	//t3.location = glm::vec3(.2, .6, 0);
	//t3.mod = Model("Textures/magic.jpg", 2);

	//t4.location = glm::vec3(0, .2, 0);
	//t4.mod = Model("Textures/magic.jpg", 2);
	//t5.location = glm::vec3(0, .4, 0);
	//t5.mod = Model("Textures/magic.jpg", 2);
	//t6.location = glm::vec3(0, .6, 0);
	//t6.mod = Model("Textures/magic.jpg", 2);

	//t7.location = glm::vec3(-.2, .2, 0);
	//t7.mod = Model("Textures/magic.jpg", 2);
	//t8.location = glm::vec3(-.2, .4, 0);
	//t8.mod = Model("Textures/magic.jpg", 2);
	//t9.location = glm::vec3(-.2, .6, 0);
	//t9.mod = Model("Textures/magic.jpg", 2);
	//
	//t10.location = glm::vec3(0, 0, 0);
	//t10.mod = Model("Textures/magic.jpg", 2);
	////makes all the tokens visible
	//for (int i = 0; i < 10; i++)
	//{
	//	tokes[i].visible = true;
	//}
}


Game::~Game()
{
}

//make camera follow player
void Game::playMove(double deltaTime, GLFWwindow* GLFWwindowPtr)
{
	if (keyIsDown[GLFW_KEY_W] && keyWasDown == keyIsDown)
	{
		robit.mod.newt(deltaTime, glm::vec3(0, 0, 0.001));
	}
	else if (keyIsDown[GLFW_KEY_S] && keyWasDown == keyIsDown)
	{
		robit.mod.newt(deltaTime, glm::vec3(0, 0, -0.001));
	}
	else if (keyIsDown[GLFW_KEY_D] && keyWasDown == keyIsDown)
	{
		robit.mod.newt(deltaTime, glm::vec3(0.001, 0, 0));
	}
	else if (keyIsDown[GLFW_KEY_A] && keyWasDown == keyIsDown)
	{
		robit.mod.newt(deltaTime, glm::vec3(-0.001, 0, 0));
	}
	else
	{
		robit.mod.clearVel();
	}

	cam.FPSControl(GLFWwindowPtr);
}

void Game::playGame(double deltaTime, GLFWwindow* GLFWwindowPtr)
{
	playMove(deltaTime, GLFWwindowPtr);
	collisions(GLFWwindowPtr);
	transMat();
	render();
}
//check all the collision and do things according to what they need done
void Game::collisions(GLFWwindow* GLFWwindowPtr)
{
	//checks to see if the player collides with any of the tokens
	//for (int i = 0; i < 10; i++)
	//{
	//	if (robit.mod.CollideWith(tokes[i].mod))
	//	{
	//		score += 50;
	//		std::cout << score << endl;
	//		tokes[i].visible = false;
	//	}
	//}
	////checks to see if the player collides with any of the walls
	//if (robit.mod.CollideWith(wall1)|| robit.mod.CollideWith(wall2) || robit.mod.CollideWith(wall3) || robit.mod.CollideWith(wall4))
	//{
	//	robit.mod.clearVel();
	//}

	////checks if the player collides with the doors
	//if (robit.mod.CollideWith(d1.mod))
	//{
	//	if (d1.correctDoor)
	//	{
	//		cout << "you selected the correct door, are you able to do it again? Let's reset!" << endl;
	//		reset();
	//	}
	//	else
	//	{
	//		cout << "you have chosen... poorly" << endl;
	//		cout << "final score: " << score << endl;
	//		glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
	//	}
	//}
	//if (robit.mod.CollideWith(d2.mod))
	//{
	//	if (d2.correctDoor)
	//	{
	//		cout << "you selected the correct door, are you able to do it again? Let's reset!" << endl;
	//		reset();
	//	}
	//	else
	//	{
	//		cout << "you have chosen... poorly" << endl;
	//		cout << "final score: " << score << endl;
	//		glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
	//	}
	//}
	//if (robit.mod.CollideWith(d3.mod))
	//{
	//	if (d3.correctDoor)
	//	{
	//		cout << "you selected the correct door, are you able to do it again? Let's reset!" << endl;
	//		reset();
	//	}
	//	else
	//	{
	//		cout << "you have chosen... poorly" << endl;
	//		cout << "final score: " << score << endl;
	//		glfwSetWindowShouldClose(GLFWwindowPtr, GL_TRUE);
	//	}
	//}
}
//this before a new round has started sets what the winning door is
void Game::selectDoor() 
{
	/*int door;
	srand(time(NULL));
	door = rand() % 3 + 1;

	switch (door) {
	case 1:
		d1.correctDoor = true;
		d2.correctDoor = false;
		d3.correctDoor = false;
		break;
	case 2:
		d2.correctDoor = true;
		d1.correctDoor = false;
		d3.correctDoor = false;
		break;
	case 3:
		d3.correctDoor = true;
		d1.correctDoor = false;
		d3.correctDoor = false;
	}*/
}

//after the round is over and the game has not ended reset everything to go back to normal
void Game::reset()
{
	/*for (int i = 0; i < 10; i++)
	{
		tokes[i].visible = true;
	}*/
	robit.location = glm::vec3(0, 0, -9);
	//selectDoor();
}

void Game::bufferModels()
{
	robit.mod.bufferModel("models/NewRobit2.obj");
	/*for (int i = 0; i < 10; i++)
	{
		if (tokes[i].visible)
		{
			tokes[i].mod.bufferModel("models/sphere.obj");
		}
	}
	d1.mod.bufferModel("models/box.obj");
	d2.mod.bufferModel("models/box.obj");
	d3.mod.bufferModel("models/box.obj");
	floor.bufferModel("models/box.obj");
	wall1.bufferModel("models/box.obj");
	wall2.bufferModel("models/box.obj");
	wall3.bufferModel("models/box.obj");
	wall4.bufferModel("models/box.obj");*/
}

void Game::loadModels()
{
	robit.mod.setup(robit.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
/*
	t1.mod.setup(t1.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	t2.mod.setup(t2.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	t3.mod.setup(t3.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	t4.mod.setup(t4.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	t5.mod.setup(t5.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	t6.mod.setup(t6.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	t7.mod.setup(t7.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	t8.mod.setup(t8.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	t9.mod.setup(t9.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	t10.mod.setup(t10.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	wall1.setup(glm::vec3(-.9, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	wall2.setup(glm::vec3(.9, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	wall3.setup(glm::vec3(0, 0, -.9), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	wall4.setup(glm::vec3(0, 0, .9), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	d1.mod.setup(d1.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	d2.mod.setup(d2.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	d3.mod.setup(d3.location, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));*/
}

//all the whatever transmat does goes here
void Game::transMat()
{
	robit.mod.transMat();
	/*for (int i = 0; i < 10; i++)
	{
		if (tokes[i].visible)
		{
			tokes[i].mod.transMat();
		}
	}
	d1.mod.transMat();
	d2.mod.transMat();
	d3.mod.transMat();
	floor.transMat();
	wall1.transMat();
	wall2.transMat();
	wall3.transMat();
	wall4.transMat();*/
}

// all the rendering is done here
void Game::render()
{
	robit.mod.render();
	/*for (int i = 0; i < 10; i++)
	{
		if (tokes[i].visible)
		{
			tokes[i].mod.render();
		}
	}
	d1.mod.render();
	d2.mod.render();
	d3.mod.render();
	floor.render();
	wall1.render();
	wall2.render();
	wall3.render();
	wall4.render();*/
}
