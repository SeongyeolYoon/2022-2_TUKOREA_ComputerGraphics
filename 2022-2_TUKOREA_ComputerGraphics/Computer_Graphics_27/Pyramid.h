#pragma once
#include "pch.h"
#include "Shader.h"

class Pyramid {
private:
	static Pyramid* pInst;

	GLfloat vertex[144] = {
		// ¾Õ¸é
		 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f,1.0f,
		-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f,
		1.0f,-1.0f, 1.0f , 0.0f, 0.0f, 1.0f, 1.0f,0.0f,

		// ¿À¸¥ÂÊ¸é
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f,1.0f,
		1.0f,-1.0f, 1.0f , 1.0f, 0.0f, 0.0f, 0.0f,0.0f,
		1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,0.0f,

		// µÞ¸é
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.5f,1.0f,
	   1.0f,-1.0f,-1.0f, 0.0f, 0.0f, -1.0f,  0.0f,0.0f,
	   -1.0f,-1.0f,-1.0f, 0.0f, 0.0f, -1.0f, 1.0f,0.0f,

	   // ¿ÞÂÊ¸é
	   0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,    0.5f,1.0f,
	   -1.0f,-1.0f,-1.0f , -1.0f, 0.0f, 0.0f,  0.0f,0.0f,
		-1.0f,-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,  1.0f,0.0f,

		// ¾Æ·§¸é
	   -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.5f,1.0f,
	   -1.0f,-1.0f,1.0f , 0.0f, -1.0f, 0.0f,  0.0f,0.0f,
		1.0f,-1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f,0.0f,

	   1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.5f,1.0f,
	   -1.0f,-1.0f,-1.0f , 0.0f, -1.0f, 0.0f,  0.0f,0.0f,
		1.0f,-1.0f, 1.0f, 0.0f, -1.0f, 0.0f,  1.0f,0.0f
	};
	std::vector<glm::vec3> colors;

	GLuint vao, vbo, colorVbo;
	GLuint texture;
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 scaleVector{ 1.0f,1.0f,1.0f};

	friend class Shader;
private:
	Pyramid();
public:
	static Pyramid* getInstance();

	void update();

	void render();
};