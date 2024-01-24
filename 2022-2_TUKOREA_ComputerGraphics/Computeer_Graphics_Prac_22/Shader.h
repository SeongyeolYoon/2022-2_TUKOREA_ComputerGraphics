#pragma once
#include "pch.h"
#include "CoordSystem.h"
#include "Hexahedron.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Orbit.h"
#include "SquarePyramid.h"

class Shader {
private:
	friend class CoordSystem;
	friend class Hexahedron;
	friend class Camera;
	friend class Light;
	friend class Sphere;
	friend class Orbit;
	friend class SquarePyramid;
	static Shader* pInst;
	GLchar* vertexSource, * fragmentSource;
	GLchar vertexShader, fragmentShader;
	GLuint shaderProgram;
private:
	Shader();
public:
	static Shader* getInstance();

	const GLuint& getShaderProgram() const;

	char* file2Buffer(const char* file);

	void makeVertexShader();

	void makeFragmentShader();

	void checkCompileError(const GLuint& shaderType, const char* name);

	void glGenerate(std::vector<Orbit*>&);

	void initShader();

	void initBuffer(std::vector<Orbit*>&);

	void release();
};
