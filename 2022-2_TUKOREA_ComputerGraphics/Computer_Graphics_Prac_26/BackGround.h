#pragma once
#include "pch.h"
#include "Shader.h"

class BackGround {
private:
	static BackGround* pInst;

	std::vector<glm::vec3> verticies;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> vertexIndices;
	std::vector<GLuint> normalIndices;
	std::vector<GLuint> uvIndices;

	GLuint vao;
	GLuint vertexVbo;
	GLuint normalVbo;
	GLuint uvVbo;
	GLuint texture;
	GLuint transformLocation;

	glm::vec3 positionVector{ 0.0f,0.0f,-8.0f };
	glm::vec3 scaleVector{ 10.0f,10.0f,0.1f };

	friend class Shader;
private:
	BackGround();
public:
	static BackGround* getInstance();

	void readObj(const char*);

	void update();

	void render();
};