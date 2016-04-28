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
	void updateTrans(float delta, glm::vec3 dForce);
	void calcMat();
	void uploadMat();
	void FPSControl(GLFWwindow* GLFWwindowPtr);
	glm::vec3 camLoc = { 0,0,2 };
	glm::vec3 camRot = { 0,0,0 };
	float pi = 3.14159;
	glm::mat3 rotMat = (glm::mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);
	glm::vec3 eye = camLoc;
	glm::vec3 center = eye + rotMat * glm::vec3(0, 0, -1);
	glm::vec3 up = rotMat * glm::vec3(0, 1, 0);
	glm::mat4 lookAtMat = glm::lookAt(eye, center, up);
	// zoom or change aspect ratio
	float zoom = 1.f;
	int width = 800;
	int height = 600;
	float fovy = 3.14159f * .4f / zoom;
	float aspect = (float)width / (float)height;
	float zNear = .01f;
	float zFar = 1000.f;
	glm::mat4 perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);

	glm::vec3 vec;
	glm::vec3 accel;

private:
	Object cam;
};

