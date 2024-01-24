#pragma once

#include "pch.h"
#include "Shader.h"
#include "Object.h"

class Planet : public Object {
private:
	glm::vec3 color{ 0.0f,0.0f,0.0f };
	glm::vec3 orbitDirection{ 0.0f,0.0f,0.0f };

	GLfloat revolutionDegree{ 0.0f };

	State curState{ State::REVOLVE };

	friend class Shader;
public:
	Planet();

	~Planet();

	virtual void initialize(const char* objName);

	virtual void readObj(const char* objName);

	virtual void update();

	virtual void render();

	virtual void release();

	void setColor(const glm::vec3&);

	void setPositionVector(const glm::vec3&);

	void setOrbitDirection(const glm::vec3&);
};