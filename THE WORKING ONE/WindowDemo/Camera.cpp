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
}


Camera::~Camera()
{
}

void Camera::updateTrans(float delta)
{
	vec = (camVel / delta) + cam.bod.velocity;

	accel = (vec - cam.bod.velocity) / delta;

	cam.bod.force = cam.bod.mass * accel;

	cam.bod.velocity = vec;

	glm::vec3 dp = cam.trans.location * cam.bod.force;
	glm::vec3 deltaR = cam.bod.velocity * delta;

	cam.trans.location += deltaR;
}

void Camera::calcMat()
{
	glm::mat3 rotMat = (glm::mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);
	glm::vec3 eye = camLoc;
	glm::vec3 center = eye + rotMat * glm::vec3(0, 0, -1);
	glm::vec3 up = rotMat * glm::vec3(0, 1, 0);
	glm::mat4 lookAtMat = glm::lookAt(eye, center, up);

	// zoom or change aspect ratio
	float zoom = 1.f;
	int width = 800;
	int height = 600;
	float fovy = pi * .4f / zoom;
	float aspect = (float)width / (float)height;
	float zNear = .01f;
	float zFar = 1000.f;
	glm::mat4 perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);

	camMat = perspectiveMat *lookAtMat;
}

void Camera::uploadMat()
{
	glUniformMatrix4fv(4, 1, GL_FALSE, &camMat[0][0]);
}

void Camera::FPSControl(GLFWwindow* GLFWwindowPtr)
{
	//turn with mouse
	float sens = .005;
	int w = 800, h = 600;
	double x, y;
	glfwGetCursorPos(GLFWwindowPtr, &x, &y);

	camRot.y -= sens *(x - w * .5f); //yaw
	camRot.x -= sens * (y - h * .5f);// pitch
	camRot.x = glm::clamp(camRot.x, -.5f * pi, .5f * pi);
	glfwSetCursorPos(GLFWwindowPtr, w * .5f, h * .5f);

	// move with arrows
	
	glm::mat3 r = (glm::mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);
	
	if (keyIsDown[GLFW_KEY_LEFT])
		camVel += r *glm::vec3(-1, 0, 0);
	if (keyIsDown[GLFW_KEY_RIGHT])
		camVel += r * glm::vec3(1, 0, 0);
	if (keyIsDown[GLFW_KEY_UP])
		camVel += r * glm::vec3(0, 0, -1);
	if (keyIsDown[GLFW_KEY_DOWN])
		camVel += r* glm::vec3(0, 0, 1);

	float speed = 1.f;
	if (camVel != glm::vec3())
		camVel = glm::normalize(camVel) * speed;
}
