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
	rotMat = (glm::mat3)glm::yawPitchRoll(cam.trans.rotation.y, cam.trans.rotation.x, cam.trans.rotation.z);
	eye = camLoc;
	center = eye + rotMat * glm::vec3(0, 0, -1);
	up = rotMat * glm::vec3(0, 1, 0);
	lookAtMat = glm::lookAt(eye, center, up);


	perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);
	camMat = perspectiveMat * lookAtMat;
	cam.trans.transMat = glm::translate(cam.trans.location) *
		glm::yawPitchRoll(cam.trans.rotation.x, cam.trans.rotation.y, cam.trans.rotation.z)*
		glm::scale(cam.trans.size);
}

void Camera::uploadMat()
{
	//glUniformMatrix4fv(4, 1, GL_FALSE, &cam.trans.transMat[0][0]);
	glUniformMatrix4fv(4, 1, GL_FALSE, &camMat[0][0]);
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
	cam.trans.rotation.x = glm::clamp(cam.trans.rotation.x, -.5f * pi, .5f * pi);
	glfwSetCursorPos(GLFWwindowPtr, w * .5f, h * .5f);

	// move with arrows
	
	glm::mat3 r = (glm::mat3)glm::yawPitchRoll(cam.trans.rotation.y, cam.trans.rotation.x, cam.trans.rotation.z);
	
	if (keyIsDown[GLFW_KEY_LEFT])
	{
		cam.bod.velocity += r *glm::vec3(-1, 0, 0); 
		cout << "left" << endl;
	}
	if (keyIsDown[GLFW_KEY_RIGHT])
	{
		cam.bod.velocity += r * glm::vec3(1, 0, 0);
		cout << "right" << endl;
	}
	if (keyIsDown[GLFW_KEY_UP])
	{
		cam.bod.velocity += r * glm::vec3(0, 0, -1);
		cout << "up" << endl;
	}
	if (keyIsDown[GLFW_KEY_DOWN])
	{
		cam.bod.velocity += r* glm::vec3(0, 0, 1);
		cout << "down" << endl;
	}
	float speed = 1.f;
	if (cam.bod.velocity != glm::vec3())
		cam.bod.velocity = glm::normalize(camVel) * speed;

	calcMat();
}
