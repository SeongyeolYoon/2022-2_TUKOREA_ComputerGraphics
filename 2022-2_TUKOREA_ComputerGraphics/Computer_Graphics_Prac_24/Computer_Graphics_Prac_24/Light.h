#pragma once

#include "pch.h"
#include "Shader.h"
#include "Object.h"

class Light : public Object{
private:
	glm::vec3 lightDirectionVector{ -4.0f,1.0f,0.0f };
	glm::vec3 lightPositionVector{ -4.0f, 1.0f, 0.0f };
	glm::vec3 lightColor{ 1.0f,1.0f,1.0f };

	GLfloat moveAmount{ 0.1f };
	GLfloat revolutionDegree{ 180.0f };

	bool revolutionTimer{ false };

	Direction revolutionDirection{ Direction::NONE };

	friend class Shader;
private:
	Light();
public:
	static GLuint color;

	static Light* getInstance();

	virtual void initialize(const char* objName);

	virtual void readObj(const char* objName);

	virtual void update();

	virtual void render();

	virtual void release();

	glm::vec3& getLightDirectionVector();

	glm::vec3& getLightPositionVector();

	glm::vec3& getLightColor();

	GLuint& getColor();

	bool& onRevolution();

	Direction& getRevolutionDirection();
};