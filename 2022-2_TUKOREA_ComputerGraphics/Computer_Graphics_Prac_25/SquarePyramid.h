#pragma once

#include "pch.h"
#include "Shader.h"

class SquarePyramid {
private:
	GLfloat verticies[18][3]{
		{ 0.0f, 1.0f, 0.0f},
		{-1.0f,-1.0f, 1.0f},
		{1.0f,-1.0f, 1.0f},
		{0.0f, 1.0f, 0.0f},
		{1.0f,-1.0f, 1.0f},
		{1.0f,-1.0f,-1.0f},
		{ 0.0f, 1.0f, 0.0f},
		{1.0f,-1.0f,-1.0f},
		{-1.0f,-1.0f,-1.0f},
		{0.0f, 1.0f, 0.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f,-1.0f, 1.0f},
		{-1.0f, -1.0f, -1.0f},
		{-1.0f,-1.0f,1.0f},
		{ 1.0f,-1.0f, 1.0f},
		{1.0f, -1.0f, -1.0f},
		{-1.0f,-1.0f,-1.0f },
		{ 1.0f,-1.0f, 1.0f}
	};

	GLfloat normals[18][3]{
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
		{1.0f, 0.0f, 0.0f },
		{1.0f, 0.0f, 0.0f },
		{1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f },
		{ -1.0f, 0.0f, 0.0f },
		{ -1.0f, 0.0f, 0.0f },
		{ -1.0f, 0.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
	};

	GLfloat color[18][3]{
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
		{0.0f, 1.0f, 1.0f},
	};
	GLuint vao;
	GLuint vertexVbo;
	GLuint normalVbo;
	GLuint colorVbo;

	glm::vec3 scaleVector{ 1.5f,1.5f,1.5f};
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };

	GLuint level{ 0 };
	friend class Shader; 

private:
	SquarePyramid();
public:
	static SquarePyramid* getInstance();

	void initialize();

	void update();

	void divideIntoSierpinski()
	{

	}

	void render();
};