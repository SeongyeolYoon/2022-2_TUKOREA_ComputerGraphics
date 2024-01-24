#pragma once
#include "pch.h"
#include "Shader.h"


class Pyramid {
private:
	static Pyramid* pInst;
	GLfloat vertex[144] = {
		// �ո�
		 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f,1.0f,
		-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f,
		1.0f,-1.0f, 1.0f , 0.0f, 0.0f, 1.0f, 1.0f,0.0f,

		// �����ʸ�
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f,1.0f,
		1.0f,-1.0f, 1.0f , 1.0f, 0.0f, 0.0f, 0.0f,0.0f,
		1.0f,-1.0f,-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,0.0f,

		// �޸�
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.5f,1.0f,
	   1.0f,-1.0f,-1.0f, 0.0f, 0.0f, -1.0f,  0.0f,0.0f,
	   -1.0f,-1.0f,-1.0f, 0.0f, 0.0f, -1.0f, 1.0f,0.0f,

	   // ���ʸ�
	   0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,    0.5f,1.0f,
	   -1.0f,-1.0f,-1.0f , -1.0f, 0.0f, 0.0f,  0.0f,0.0f,
		-1.0f,-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,  1.0f,0.0f,

		// �Ʒ���
	   -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.5f,1.0f,
	   -1.0f,-1.0f,1.0f , 0.0f, -1.0f, 0.0f,  0.0f,0.0f,
		1.0f,-1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f,0.0f,

	   1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.5f,1.0f,
	   -1.0f,-1.0f,-1.0f , 0.0f, -1.0f, 0.0f,  0.0f,0.0f,
		1.0f,-1.0f, 1.0f, 0.0f, -1.0f, 0.0f,  1.0f,0.0f
	};

	GLuint vao, vbo;
	GLuint texture;
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 scaleVector{ 0.5f,0.5f,0.5f };

	friend class Shader;
private:
	Pyramid();
public:
	static Pyramid* getInstance();

	void update();

	void render();
};