#pragma once

#include "pch.h"
#include "CoordSystem.h"
#include "Camera.h"
#include "Cube.h"
#include "Pyramid.h"
#include "BackGround.h"

class Shader {
private:
	static Shader* pInst;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;

	friend class Camera;
	friend class CoordSystem;
	friend class Cube;
	friend class Pyramid;
	friend class BackGround;
private:
	Shader()
	{

	}
public:
	static Shader* getInstance();

	const GLuint& getShaderProgram() { return shaderProgram; }

	char* file2Buffer(const char* file);

	void makeVertexShader();

	void makeFragmentShader();

	void checkCompileError(const GLuint& shaderType, const char* name);

	void glGenerate();

	void initTexture();

	void initShader();

	void initBuffer();

	void release();
};