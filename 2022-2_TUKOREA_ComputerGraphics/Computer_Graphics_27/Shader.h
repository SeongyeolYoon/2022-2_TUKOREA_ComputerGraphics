#pragma once

#include "pch.h"
#include "Camera.h"
#include "Light.h"
#include "Floor.h"
#include "Pyramid.h"
#include "Pillar.h"
#include "Snow.h"

class Shader {
private:
	static Shader* pInst;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;

	friend class Camera;
	friend class Light;
	friend class Floor;
	friend class Pyramid;
	friend class Pillar;
	friend class Snow;
private:
	Shader();
public:
	static Shader* getInstance();

	const GLuint& getShaderProgram();

	char* file2Buffer(const char* file);

	void makeVertexShader();

	void makeFragmentShader();

	void checkCompileError(const GLuint& shaderType, const char* name);

	void glGenerate(std::vector<Pillar*>&, std::vector<Snow*>&);

	void initTexture(std::vector<Pillar*>&, std::vector<Snow*>&);

	void initShader();

	void initBuffer(std::vector<Pillar*>&, std::vector<Snow*>&);

	void release();
};