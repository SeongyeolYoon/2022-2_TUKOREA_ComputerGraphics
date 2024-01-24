#pragma once

#include "pch.h"
#include "Shader.h"

class Sphere {
	friend class Shader;
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	std::vector<GLuint> vertexIndices;
	std::vector<GLuint> uvIndices;
	std::vector<GLuint> normalIndices;

	glm::vec3 m_positionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 m_color{ 0.0f,0.0f,0.0f };

	GLuint vao;
	GLuint positionVbo;
	GLuint normalVbo;
	GLuint colorVbo;

	GLfloat rotatationDegree{ 0.0f };
	bool onRotation{ false };
public:
	Sphere();

	void readObj(const char*);

	GLfloat& getRotationDegree();

	void setPositionVector(const glm::vec3&);

	void setColor(const glm::vec3&);

	bool& isOnRotation();

	void render(glm::mat4& parent) const;
};