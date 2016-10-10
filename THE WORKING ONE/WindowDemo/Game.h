#pragma once
#include "Model.h"
#include "Camera.h"
#include <time.h>
#include <string>

struct Player
{
	Model mod;
	glm::vec3 location;
};

struct Token
{
	Model mod;
	bool visible;
	glm::vec3 location;
};
struct Door
{
	Model mod;
	bool correctDoor;
	glm::vec3 location;
};
class Game
{
public:
	Game();
	~Game();
	void playMove(double deltaTime, GLFWwindow* GLFWwindowPtr); // this as the character move around, camera stuff probably
	void playGame(double deltaTime, GLFWwindow* GLFWwindowPtr); //heres where the fun happens
	void bufferModels(); //makes the models become a thing
	void loadModels(); //helps put everything in its place

private:
	int score; //this will go up with every token collected
	void collisions(GLFWwindow* GLFWwindowPtr); //all the collision checks will be done here
	void selectDoor(); //randomly picks the winning door
	void reset();  //everything is put back in its place
	void transMat();
	void render();
	// the things within the game
	Player robit;
	Token t1;
	Token t2;
	Token t3;
	Token t4;
	Token t5;
	Token t6;
	Token t7;
	Token t8;
	Token t9;
	Token t10;

	//holds all the tokens
	Token tokes[10] = { t1,t2,t3,t4,t5,t6,t7,t8,t9,t10 };

	//dank doors
	Door d1;
	Door d2;
	Door d3;

	Model floor = Model("Textures/floor.jpg", 3); //has aabb collision type
	Model wall1 = Model("Textures/floor.jpg", 3); //has aabb collision type
	Model wall2 = Model("Textures/floor.jpg", 3); //has aabb collision type
	Model wall3 = Model("Textures/floor.jpg", 3); //has aabb collision type
	Model wall4 = Model("Textures/floor.jpg", 3); //has aabb collision type

	Camera cam = Camera();
};

