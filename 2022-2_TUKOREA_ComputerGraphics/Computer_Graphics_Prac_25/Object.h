#pragma once
#include "pch.h"

class Object {
public:
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> vertexIndices;
	std::vector<GLuint> normalIndices;
	std::vector<GLuint> uvIndices;

	GLuint vao;
	GLuint vertexVbo;
	GLuint normalVbo;
	GLuint colorVbo;
	GLuint uvVbo;

	GLuint transformLocation;

	glm::vec3 scaleVector{ 0.0f,0.0f,0.0f };
	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
public:
	Object();

	virtual ~Object();
public:
	virtual void initialize(const char*) = 0;
	virtual void readObj(const char*) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void release() = 0;
};