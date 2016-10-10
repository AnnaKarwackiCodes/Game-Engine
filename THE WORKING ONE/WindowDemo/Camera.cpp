#include "Camera.h"

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

Camera::Camera()
{
	cam.bod.mass = 0.0f;
	cam.bod.force = glm::vec3(0, 0, 0);
	cam.bod.velocity = glm::vec3(0, 0, 0);
	cam.trans.location = glm::vec3(0, 0, 2);
	cam.trans.rotation = glm::vec3(0, 0, 0);
}


Camera::~Camera()
{
}

void Camera::updateTrans(float delta)
{

	vec = (cam.bod.velocity * delta) + cam.bod.velocity;

	accel = (vec - cam.bod.velocity) * delta;

	cam.bod.force = cam.bod.mass * accel;

	cam.bod.velocity = vec;

	glm::vec3 dp = cam.trans.location * cam.bod.force;
	glm::vec3 deltaR = cam.bod.velocity * delta;

	cam.trans.location += deltaR;
}

void Camera::updateVel(glm::vec3 vel)
{
	glm::mat3 r = (glm::mat3)glm::yawPitchRoll(cam.trans.rotation.y, cam.trans.rotation.x, cam.trans.rotation.z);
	cam.bod.velocity += r * vel;

	float speed = 1.f;
	if (cam.bod.velocity != glm::vec3())
		cam.bod.velocity = glm::normalize(cam.bod.velocity) * speed;
}

void Camera::calcMat(glm::vec3 location)
{
	rotMat = (glm::mat3)glm::yawPitchRoll(cam.trans.rotation.y, cam.trans.rotation.x, cam.trans.rotation.z);
	eye = cam.trans.location;
	center = eye + rotMat * glm::vec3(0, 0, -1);
	//center = location;
	up = rotMat * glm::vec3(0, 1, 0);
	lookAtMat = glm::lookAt(eye, center, up);
	//lookAtMat = location;
	perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);
	camMat = perspectiveMat * lookAtMat;
	cam.trans.transMat = glm::translate(cam.trans.location) * glm::yawPitchRoll(cam.trans.rotation.x, cam.trans.rotation.y, cam.trans.rotation.z) * glm::scale(cam.trans.size);
}

void Camera::uploadMat()
{
	glUniformMatrix4fv(4, 1, GL_FALSE, &camMat[0][0]);
	glUniform3f(6, cam.trans.location.x, cam.trans.location.y, cam.trans.location.z);
}

void Camera::FPSControl(GLFWwindow* GLFWwindowPtr)
{
	//turn with mouse
	float sens = .005;
	int w = 800, h = 600;
	double x, y;
	glfwGetCursorPos(GLFWwindowPtr, &x, &y);
	
	cam.trans.rotation.y -= sens *(x - w * .5f); //yaw
	cam.trans.rotation.x -= sens * (y - h * .5f);// pitch
	cam.trans.rotation.x = glm::clamp(cam.trans.rotation.x, -.5f * (float)M_PI, .5f * (float)M_PI);
	glfwSetCursorPos(GLFWwindowPtr, w * .5f, h * .5f);

	//camRot = cam.trans.rotation;
	// move with arrows

	//calcMat();
}

void Camera::clearVel()
{
	cam.bod.velocity = { 0,0,0 };
}
