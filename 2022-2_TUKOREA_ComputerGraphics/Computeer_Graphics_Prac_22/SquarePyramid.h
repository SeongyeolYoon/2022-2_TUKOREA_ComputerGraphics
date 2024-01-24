#pragma once
#include "pch.h"
#include "Shader.h"

class SquarePyramid {
private:
	GLfloat vertex[108] = {
		// ¾Õ¸é
		 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f,-1.0f, 1.0f , 0.0f, 0.0f, 1.0f,

		// ¿À¸¥ÂÊ¸é
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f,-1.0f, 1.0f , 1.0f, 0.0f, 0.0f,
		 1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f,

		 // µÞ¸é
		 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		1.0f,-1.0f,-1.0f, 0.0f, 0.0f, -1.0f,
		-1.0f,-1.0f,-1.0f, 0.0f, 0.0f, -1.0f,

		// ¿ÞÂÊ¸é
		0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,-1.0f,-1.0f , -1.0f, 0.0f, 0.0f,
		 -1.0f,-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		 // ¾Æ·§¸é
		-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
		-1.0f,-1.0f,1.0f , 0.0f, -1.0f, 0.0f,
		 1.0f,-1.0f, 1.0f, 0.0f, -1.0f, 0.0f,

		1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
		-1.0f,-1.0f,-1.0f , 0.0f, -1.0f, 0.0f,
		 1.0f,-1.0f, 1.0f, 0.0f, -1.0f, 0.0f
	};

	GLfloat color[18][3]{
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	};

	GLuint vao, vbo[2];
	GLfloat rotationDegree{ 0.0f };
	bool onRotation{ false };

	friend class Shader;
public:
	static SquarePyramid* getInstance();

	GLfloat& getRotationDegree();

	bool& isOnRotation();

	void render(const glm::mat4& parent);
};