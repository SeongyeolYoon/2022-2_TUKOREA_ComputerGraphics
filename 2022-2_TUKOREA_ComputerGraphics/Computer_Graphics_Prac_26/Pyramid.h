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
	GLuint textures[6];
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 scaleVector{ 0.5f,0.5f,0.5f };

	GLfloat xRotationDegree{ 0.0f };
	GLfloat yRotationDegree{ 0.0f };
	bool onRotation{ false };

	Axis axis{ Axis::NONE };
	Direction direction{ Direction::NONE };

	friend class Shader;
private:
	Pyramid();
public:
	static Pyramid* getInstance();

	Direction& getDirection();
	Axis& getAxis();
	bool& isOnRotation();

	void update();

	void render(glm::mat4& parent);
};