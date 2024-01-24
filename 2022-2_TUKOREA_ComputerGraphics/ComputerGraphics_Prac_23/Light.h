#pragma once
#include "pch.h"
#include "Shader.h"

class Light {
private:
	friend class Shader;
	static Light* pInst;
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

	glm::vec3 directionVector{ 0.0f,0.0f, 0.0f };
	glm::vec3 lightPos{ 3.0f, 0.0f, 0.0f };
	glm::vec3 lightColor{ 0.0f,0.0f,0.0f };
	glm::vec3 positionVector{ 3.0f,0.0f,0.0f };
	GLfloat posDegree{ 0.0f };
	GLfloat lightPosDegree{ 0.0f };
	GLfloat moveAMount{ 0.1f };
	GLfloat revolutionDegree{ 0.0f };
	bool onLight{ false };
	bool onRevolution{ false };
	Direction revolutionDirection{ Direction::NONE };
	LightColor lightColorType{ LightColor::NONE };
private:
	Light();
public:
	static Light* getInstance();

	void readObj(const char* fileName);

	void on();

	void off();

	bool& isOnRight();

	glm::vec3& getLightColor();

	glm::vec3& getLightPos();

	GLfloat& getPosDegree();

	glm::vec3& getDirectionVector();

	glm::vec3& getPositionVector();

	GLfloat& getLightPosDegree();

	GLfloat& getMoveAmount();

	bool& isOnRevolution();

	Direction& getRevolutionDirection();

	LightColor& getLightColorType();

	GLfloat& getRevolutionDegree();

	void render(glm::mat4&) const;
};
