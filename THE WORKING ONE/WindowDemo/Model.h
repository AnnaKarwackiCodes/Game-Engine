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

#include <iostream>
#include <map>
#include <cmath>

class Model
{
	struct Transform {
		glm::vec3 location;
		glm::vec3 rotation;
		glm::vec3 size;
		glm::mat4 transMat;
	};
	struct rigidBody {
		glm::vec3 velocity;
		glm::vec3 force;
		float mass;
	};
	struct Object {
		Transform trans;
		string fileName;
		rigidBody bod;
	};
	struct Vertex {
		glm::vec3 loc;
		glm::vec2 uv;
	};

public:
	Model();
	Model(char* nm, int type);
	~Model();
	void transMat();
	bool render();
	bool bufferModel();
	bool setup();
	bool setup(glm::vec3 loc, glm::vec3 size, glm::vec3 rot);
	void newt(float delta, glm::vec3 dForce);
	glm::vec3 vec;
	void clearVel();
	bool CollideWith(const Model& mod);
	int collisionType;
	void TextureChange(char* nm);

private:
	Object obj;
	Texture text;
	GLuint vertArr;
	unsigned int vertCount;
	char* name;
	glm::vec3 accel;
	
};

