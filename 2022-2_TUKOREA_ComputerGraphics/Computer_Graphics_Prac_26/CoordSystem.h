#pragma once
#include "pch.h"
#include "Shader.h"
class CoordSystem {
private:
	friend class Shader;
	static CoordSystem* pInst;
	const GLfloat vertex[6][3]{
		{-2.0f,0.0f,0.0f}, {2.0f,0.0f,0.0f},
		{0.0f,-2.0f,0.0f}, {0.0f,2.0f,0.0f},
		{0.0f,0.0f,-2.0f}, {0.0f,0.0f,2.0f} };
	const GLfloat color[6][3]{
		{1.0f,0.0f,0.0f}, {1.0f,0.0f,0.0f},
		{0.0f,1.0f,0.0f}, {0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f}, {0.0f,0.0f,1.0f} };

	GLuint vao, vbo[2];
private:
	CoordSystem();
public:
	static CoordSystem* getInstance();

	glm::mat4 render() const;
};