#pragma once
#include "pch.h"
#include "Shader.h"

class Hexahedron {
private:
	friend class Shader;
	static Hexahedron* pInst;
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
	
	GLfloat rotatationDegree{ 0.0f };
	bool onRotation{ false };
private:
	Hexahedron();
public:
	
	static Hexahedron* getInstance();

	void readObj(const char* fileName);

	GLfloat& getRotationDegree();

	bool& isOnRotation();

	void render(glm::mat4&) const;
};