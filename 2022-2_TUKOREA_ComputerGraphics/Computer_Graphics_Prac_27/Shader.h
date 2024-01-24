#pragma once

#include "pch.h"
#include "Camera.h"
#include "Light.h"
#include "Floor.h"
#include "Pillar.h"
#include "Snow.h"
#include "Object.h"
#include "Pyramid.h"

class Shader {
private:
	static Shader* pInst;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;

	friend class Camera;
	friend class Light;
	friend class Floor;
	friend class Pillar;
	friend class Snow;
	friend class Pyramid;
	friend class Object;
private:
	Shader();
public:
	static Shader* getInstance();

	const GLuint& getShaderProgram();

	char* file2Buffer(const char* file);

	void makeVertexShader();

	void makeFragmentShader();

	void checkCompileError(const GLuint& shaderType, const char* name);

	void glGenerate(std::vector<Snow*>&, std::vector<Pillar*>&);

	void initTexture(std::vector<Snow*>&, std::vector<Pillar*>&);

	void initShader();

	void initBuffer(std::vector<Snow*>&, std::vector<Pillar*>&);

	void release();
};