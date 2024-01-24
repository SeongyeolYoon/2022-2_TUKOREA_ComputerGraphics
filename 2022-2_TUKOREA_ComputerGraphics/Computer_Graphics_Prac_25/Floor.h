#pragma once
#include "pch.h"
#include "Object.h"
#include "Shader.h"

class Floor : public Object {
private:
	friend class Shader;

	glm::vec3 scaleVector{ 0.0f,0.0f,0.0f };
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };

	GLuint transformLocation;


private:
	Floor();
public:
	static Floor* getInstance();

	virtual void initialize(const char* objName);

	virtual void readObj(const char* objName);

	virtual void update();

	virtual void render();

	virtual void release();
};