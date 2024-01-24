#pragma once

#include "Object.h"
#include "Shader.h"

class Snow : public Object {
private:
	std::mt19937 mersenne{ std::random_device{}() };
	std::uniform_real_distribution<GLfloat> randomXPos{ -5.0f,5.0f };
	std::uniform_real_distribution<GLfloat> randomZPos{ -5.0f,5.0f };
	std::uniform_real_distribution<GLfloat> randomFallSpeed{ 0.01f,0.03f };

	GLfloat fallSpeed;

	State curState{ State::IDLE };
public:
	Snow() = default;

	virtual void initialize(const char* objName);

	virtual void readObj(const char* objName);

	virtual void update();

	virtual void render();

	virtual void release();

	void setState(State state);

	friend class Shader;
};