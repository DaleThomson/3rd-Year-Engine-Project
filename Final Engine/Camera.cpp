#include "Camera.h"

namespace camera
{
	glm::vec3 eye = glm::vec3(-30.0f, 10.0f, 0.0f);
	glm::vec3 at = glm::vec3(0.0f, 1.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 getEye()
	{
		return eye;
	}
	glm::vec3 getAt()
	{
		return at;
	}
	glm::vec3 getUp()
	{
		return up;
	}
	void setEye(glm::vec3 newEye)
	{
		eye = newEye;
	}
	void setAt(glm::vec3 newAt)
	{
		at = newAt;
	}
	void setUp(glm::vec3 newUp)
	{
		up = newUp;
	}
}