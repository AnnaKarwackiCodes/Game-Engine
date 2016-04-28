#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "FreeImage.h"

#include <vector>
#include <string>
#include <map>
class Camera
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
		rigidBody bod;
	};
public:
	Camera();
	~Camera();
	glm::mat4 upload;
	void updateTrans(float delta);
	void calcMat();
	void uploadMat();
	void FPSControl(GLFWwindow* GLFWwindowPtr);
	glm::mat4 camMat;
	glm::vec3 camLoc = { 0,0,2 };
	glm::vec3 camRot = { 0,0,0 };
	float pi = 3.14159;
	glm::vec3 camVel;

	glm::vec3 vec;
	glm::vec3 accel;

private:
	Object cam;
};

