#pragma once
#include "pch.h"
#include "Shader.h"

class Orbit {
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	std::vector<GLuint> vertexIndices;
	std::vector<GLuint> uvIndices;
	std::vector<GLuint> normalIndices;

	GLuint vao;
	GLuint positionVbo;
	GLuint normalVbo;
	GLuint colorVbo;

	GLfloat degree{ 0.0f };
	GLfloat radian{ 260.0f };

	glm::vec3 scaleVector{ 0.0f,0.0f,0.0f };
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 colorVector{ 0.0f,0.0f,0.0f };
	friend class Shader;
public:
	Orbit(const GLfloat& degreeIn);

	void initialize(const char* objName);

	void readObj(const char* objName);

	void update();

	void render(const glm::mat4&);

	GLfloat& getRadian() { return radian; }
};