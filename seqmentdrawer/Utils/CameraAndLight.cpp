#include "CameraAndLight.h"

Camera::Camera(const glm::vec3& e, const glm::vec3& u)
	: eye(e),up(u)
{
	at = glm::vec3(0, 0, 0);
}


void Camera::Add(const glm::vec3& unit)
{
	if (eye.z + unit.z < 5) return;

	eye += unit;
	at += unit;
}
void Camera::Sub(const glm::vec3& unit)
{
	eye -= unit;
	at -= unit;
}
