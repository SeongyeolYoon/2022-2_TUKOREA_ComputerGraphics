#pragma once
#include "pch.h"
#include "Shader.h"

class Camera {
private:
	friend class Shader;
	static Camera* pInst;
	glm::vec3 positionVector{ glm::vec3{0.0f,0.0f,10.0f} };
	glm::vec3 targetVector{ glm::vec3{0.0f,0.0f,0.0f} };
	//glm::vec3 directionVector{ glm::vec3{0.0f,0.0f,0.0f} };
	glm::vec3 directionVector{ glm::normalize(targetVector - positionVector) };
	glm::vec3 defaultUpVector{ glm::vec3{ 0.0f,1.0f,0.0f } };
	glm::vec3 rightVector{ glm::normalize(glm::cross(defaultUpVector, directionVector)) };
	glm::vec3 upVector{ glm::cross(directionVector, rightVector) };
	glm::vec3 front{ glm::vec3{ 0.0f,0.0f,-1.0f } };
	glm::mat4 viewMatrix{ 1.0f };
	glm::mat4 projectionMatrix{ 1.0f };
	GLfloat speed{ 0.1f };
	GLfloat rotationDegree{ 0.0f };
	bool onRotation{ false };
private:
	Camera();
public:
	static Camera* getInstance();
	glm::vec3& getPositionVector();
	glm::vec3& getTargetVector();
	glm::vec3& getDirectionVector();
	glm::vec3& getUpVector();
	glm::vec3& getRightVector();
	glm::vec3& getDefaultUpVector();

	bool& isOnRotation();

	GLfloat& getRotationDegree();

	void update();
};