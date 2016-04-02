#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
	 Camera(const glm::vec3& = glm::vec3(0, 0, 40), const glm::vec3& = glm::vec3(0, 1, 0));
	~Camera() {  }

	glm::vec3 GetEye() const { return eye; }
	glm::vec3 GetUp() const { return up; }
	glm::vec3 GetAt() const { return at; }
	glm::vec3 GetVertUnit() const { return glm::vec3(0, 1, 0); }
	glm::vec3 GetZoomUnit() const { return glm::vec3(0, 0, -1);}

	glm::vec3 GetCameraUnit() const { return glm::vec3(-1, 0, 0); }

	void Add(const glm::vec3&);
	void Sub( const glm::vec3&);

protected:

	glm::vec3 eye;
	glm::vec3 up;
	glm::vec3 at;


private:

};
