#pragma once

#include "Object.h"
#include "Shader.h"

class Pillar : public Object {
private:
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_real_distribution<GLfloat> randomXPos{ -3.0f,3.0f };
	std::uniform_real_distribution<GLfloat> randomZPos{ -3.0f,3.0f };
public:
	Pillar() = default;

	virtual void initialize(const char* objName);

	virtual void readObj(const char* objName);

	virtual void update();

	virtual void render();

	virtual void release();

	friend class Shader;
};