#pragma once
#include "pch.h"
#include "Shader.h"

class Cube {
private:
	static Cube* pInst;

	std::vector<glm::vec3> verticies;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> vertexIndices;
	std::vector<GLuint> normalIndices;
	std::vector<GLuint> uvIndices;

	GLuint vao;
	GLuint vertexVbo;
	GLuint normalVbo;
	GLuint uvVbo;
	GLuint textures[6];
	GLuint transformLocation;

	glm::vec3 positionVector{ 0.0f,0.0f,0.0f };
	glm::vec3 scaleVector{ 0.5f,0.5f,0.5f };

	GLfloat xRotationDegree{ 0.0f };
	GLfloat yRotationDegree{ 0.0f };

	bool onRotation{ false };

	Axis axis{ Axis::NONE };
	Direction direction{ Direction::NONE };

	friend class Shader;
private:
	Cube();
public:
	static Cube* getInstance();

	Direction& getDirection();
	Axis& getAxis();
	bool& isOnRotation();

	void readObj(const char*);

	void update();

	void render(glm::mat4&);
};