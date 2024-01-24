#pragma once
#include "pch.h"
#include "Object.h"
#include "Floor.h"
#include "Camera.h"
#include "Light.h"
#include "Snow.h"
#include "Planet.h"
#include "SquarePyramid.h"

class Shader {
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;

	friend class Floor;
	friend class Camera;
	friend class Light;
	friend class Snow;
	friend class Planet;
	friend class SqaurePyramid;
private:
	Shader();

public:
	static Shader* getInstance();

	const GLuint& getShaderProgram() const;

	char* file2Buffer(const char* file);

	void makeVertexShader();

	void makeFragmentShader();

	void checkCompileError(const GLuint& shaderType, const char* name);

	void glGenerate(std::vector<Snow*>&, std::vector<Planet*>&);

	void initShader();

	void initBuffer(std::vector<Snow*>&, std::vector<Planet*>&);

	void release();
};