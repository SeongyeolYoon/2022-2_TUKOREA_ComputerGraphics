#include "Camera.h"

Camera* Camera::pInst = nullptr;

Camera::Camera()
{

}

Camera* Camera::getInstance()
{
	if (nullptr == pInst)
		pInst = new Camera;

	return pInst;
}

glm::vec3& Camera::getPositionVector()
{
	return positionVector;
}

glm::vec3& Camera::getLookVector()
{
	return lookVector;
}

glm::vec3& Camera::getDirectionVector()
{
	return directionVector;
}

glm::vec3& Camera::getUpVector()
{
	return upVector;
}

glm::vec3& Camera::getRightVector()
{
	return rightVector;
}

glm::vec3& Camera::getDefaultUpVector()
{
	return defaultUpVector;
}

void Camera::update()
{
	viewMatrix = glm::lookAt(positionVector, lookVector, upVector);
	projectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 50.0f);
	unsigned int viewTrasnformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "viewTransform");
	unsigned int projectionTransformLocation = glGetUniformLocation(Shader::getInstance()->getShaderProgram(), "projectionTransform");
	glUniformMatrix4fv(viewTrasnformLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}
