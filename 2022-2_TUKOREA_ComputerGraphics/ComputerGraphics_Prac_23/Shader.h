#pragma once
#include "pch.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"

class Shader {
private:
	friend class Camera;
	friend class Light;
	friend class Sphere;
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

	void glGenerate(std::vector<Sphere*>&);

	void initShader();

	void initBuffer(std::vector<Sphere*>&);

	void release();
};
