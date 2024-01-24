#pragma once

#include "pch.h"
#include "Floor.h"
#include "Camera.h"
#include "Light.h"
#include "Crane.h"

class Shader {
private:
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;

	friend class Floor;
	friend class Camera;
	friend class Light;
	friend class Crane;
private:
	Shader();

public:
	static Shader* getInstance();

	const GLuint& getShaderProgram() const;

	char* file2Buffer(const char* file);

	void makeVertexShader();

	void makeFragmentShader();

	void checkCompileError(const GLuint& shaderType, const char* name);

	void glGenerate();

	void initShader();

	void initBuffer();

	void release();
};