#pragma once
#include "pch.h"
#include "Shader.h"

class Light {
private:
	static Light* pInst;
	glm::vec3 lightColor{ 1.0f,1.0f,1.0f };
	glm::vec3 positionVector{ -1.0f,3.0f,0.0f };
	friend class Shader;
private:
	Light();
public:
	static Light* getInstance();

	void initialize();

	glm::vec3& getLightColor();

	glm::vec3 getPosition();
};